#include "visualizer.h"

#include <SFML/Config.hpp>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <filesystem>
#include <iomanip>
#include <limits>
#include <sstream>
#include <string>
#include <thread>

namespace Sorting
{
    namespace
    {
        sf::RenderWindow createWindow(const int width, const int height)
        {
#if SFML_VERSION_MAJOR >= 3
            return sf::RenderWindow(
                sf::VideoMode({static_cast<unsigned int>(width), static_cast<unsigned int>(height)}),
                "RamplangC Sorting Visualizer",
                sf::Style::Default);
#else
            return sf::RenderWindow(
                sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)),
                "RamplangC Sorting Visualizer",
                sf::Style::Default);
#endif
        }

        float elapsedSecondsSince(const std::chrono::steady_clock::time_point& start)
        {
            const auto elapsed = std::chrono::steady_clock::now() - start;
            return std::chrono::duration<float>(elapsed).count();
        }

        bool loadFontFromFile(sf::Font& font, const std::filesystem::path& path)
        {
#if SFML_VERSION_MAJOR >= 3
            return font.openFromFile(path);
#else
            return font.loadFromFile(path.string());
#endif
        }

        std::vector<std::int16_t> makeTone(
            const float frequency,
            const float durationSeconds,
            const float volume)
        {
            constexpr unsigned int sampleRate = 44100;
            constexpr float pi = 3.14159265358979323846F;

            const auto sampleCount = static_cast<std::size_t>(sampleRate * durationSeconds);
            std::vector<std::int16_t> samples(sampleCount);

            for (std::size_t i = 0; i < sampleCount; ++i)
            {
                const float t = static_cast<float>(i) / static_cast<float>(sampleRate);
                const float fade = 1.0F - (static_cast<float>(i) / static_cast<float>(sampleCount));
                const float wave = std::sin(2.0F * pi * frequency * t);
                const float value = wave * fade * volume * static_cast<float>(std::numeric_limits<std::int16_t>::max());
                samples[i] = static_cast<std::int16_t>(value);
            }

            return samples;
        }

        bool loadMonoSamples(sf::SoundBuffer& buffer, const std::vector<std::int16_t>& samples)
        {
            constexpr unsigned int channelCount = 1;
            constexpr unsigned int sampleRate = 44100;

#if SFML_VERSION_MAJOR >= 3
            return buffer.loadFromSamples(
                samples.data(),
                static_cast<std::uint64_t>(samples.size()),
                channelCount,
                sampleRate,
                {sf::SoundChannel::Mono});
#else
            return buffer.loadFromSamples(
                samples.data(),
                static_cast<sf::Uint64>(samples.size()),
                channelCount,
                sampleRate);
#endif
        }
    }

    Visualizer::Visualizer(const int width, const int height, const int fps)
        : window(createWindow(width, height)),
          targetFps(std::max(1, fps)),
          startTime(std::chrono::steady_clock::now()),
          fpsWindowStart(startTime)
    {
        window.setFramerateLimit(static_cast<unsigned int>(targetFps));
        loadFont();
        loadSounds();
    }

    void Visualizer::compare(const int a, const int b)
    {
        currentA = a;
        currentB = b;
        swapped = false;
        ++comparisonCount;
        playCompareSound();
    }

    void Visualizer::swap(const int a, const int b)
    {
        currentA = a;
        currentB = b;
        swapped = true;
        ++swapCount;
        playSwapSound();
    }

    void Visualizer::update(const std::vector<int>& arr)
    {
        values = arr;
        finished = false;

        processPause();

        if (!isOpen())
        {
            return;
        }

        pollEvents();
        draw();
        window.display();
        updateFps();

        std::this_thread::sleep_for(std::chrono::milliseconds(animationDelayMs));
    }

    void Visualizer::finish()
    {
        finished = true;
        currentA = -1;
        currentB = -1;
        swapped = false;

        while (isOpen() && !restartRequested && !randomizeRequested)
        {
            pollEvents();
            draw();
            window.display();
            updateFps();

            std::this_thread::sleep_for(std::chrono::milliseconds(animationDelayMs));
        }
    }

    bool Visualizer::isOpen() const
    {
        return window.isOpen();
    }

    void Visualizer::pollEvents()
    {
#if SFML_VERSION_MAJOR >= 3
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (const auto* resized = event->getIf<sf::Event::Resized>())
            {
                window.setView(sf::View(sf::FloatRect(
                    {0.0F, 0.0F},
                    {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)})));
            }
            else if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
                else if (key->code == sf::Keyboard::Key::Space)
                {
                    paused = !paused;
                }
                else if (key->code == sf::Keyboard::Key::R)
                {
                    restartRequested = true;
                    paused = false;
                }
                else if (key->code == sf::Keyboard::Key::N)
                {
                    randomizeRequested = true;
                    paused = false;
                }
                else if (key->code == sf::Keyboard::Key::M)
                {
                    soundEnabled = !soundEnabled;
                }
                else if (key->code == sf::Keyboard::Key::Up || key->code == sf::Keyboard::Key::Add)
                {
                    setDelay(animationDelayMs - 5);
                }
                else if (key->code == sf::Keyboard::Key::Down || key->code == sf::Keyboard::Key::Subtract)
                {
                    setDelay(animationDelayMs + 5);
                }
            }
        }
#else
        sf::Event event {};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::Resized)
            {
                window.setView(sf::View(sf::FloatRect(
                    0.0F,
                    0.0F,
                    static_cast<float>(event.size.width),
                    static_cast<float>(event.size.height))));
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Space)
                {
                    paused = !paused;
                }
                else if (event.key.code == sf::Keyboard::R)
                {
                    restartRequested = true;
                    paused = false;
                }
                else if (event.key.code == sf::Keyboard::N)
                {
                    randomizeRequested = true;
                    paused = false;
                }
                else if (event.key.code == sf::Keyboard::M)
                {
                    soundEnabled = !soundEnabled;
                }
                else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Add)
                {
                    setDelay(animationDelayMs - 5);
                }
                else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Subtract)
                {
                    setDelay(animationDelayMs + 5);
                }
            }
        }
#endif
    }

    void Visualizer::setDelay(const int milliseconds)
    {
        animationDelayMs = std::clamp(milliseconds, 0, 1000);
    }

    void Visualizer::setSoundEnabled(const bool enabled)
    {
        soundEnabled = enabled;
    }

    void Visualizer::resetStatistics()
    {
        currentA = -1;
        currentB = -1;
        swapped = false;
        finished = false;
        paused = false;
        comparisonCount = 0;
        swapCount = 0;
        measuredFps = 0.0;
        framesThisSecond = 0;
        startTime = std::chrono::steady_clock::now();
        fpsWindowStart = startTime;
    }

    bool Visualizer::shouldStop() const
    {
        return !isOpen() || restartRequested || randomizeRequested;
    }

    bool Visualizer::consumeRestartRequest()
    {
        const bool requested = restartRequested;
        restartRequested = false;
        return requested;
    }

    bool Visualizer::consumeRandomizeRequest()
    {
        const bool requested = randomizeRequested;
        randomizeRequested = false;
        return requested;
    }

    std::uint64_t Visualizer::getComparisonCount() const
    {
        return comparisonCount;
    }

    std::uint64_t Visualizer::getSwapCount() const
    {
        return swapCount;
    }

    double Visualizer::getElapsedTime() const
    {
        return elapsedSecondsSince(startTime);
    }

    double Visualizer::getFps() const
    {
        return measuredFps;
    }

    int Visualizer::getDelay() const
    {
        return animationDelayMs;
    }

    std::size_t Visualizer::getArraySize() const
    {
        return values.size();
    }

    void Visualizer::draw()
    {
        window.clear(sf::Color(18, 18, 20));
        drawBars();
        drawStatistics();
    }

    void Visualizer::drawBars()
    {
        if (values.empty())
        {
            return;
        }

        const sf::Vector2u windowSize = window.getSize();
        const auto maxValue = static_cast<float>(*std::max_element(values.begin(), values.end()));
        const float drawableHeight = std::max(1.0F, static_cast<float>(windowSize.y) - topPanelHeight - 16.0F);
        const float barAreaTop = topPanelHeight;
        const float barAreaBottom = static_cast<float>(windowSize.y) - 8.0F;
        const float barSlotWidth = static_cast<float>(windowSize.x) / static_cast<float>(values.size());
        const float barWidth = std::max(1.0F, barSlotWidth - 1.0F);

        sf::RectangleShape bar;

        for (std::size_t i = 0; i < values.size(); ++i)
        {
            const float normalized = maxValue <= 0.0F
                ? 0.0F
                : static_cast<float>(values[i]) / maxValue;
            const float height = std::max(2.0F, std::floor(normalized * drawableHeight));
            const float x = static_cast<float>(i) * barSlotWidth;
            const float y = std::max(barAreaTop, barAreaBottom - height);

            bar.setSize(sf::Vector2f(barWidth, barAreaBottom - y));
            bar.setPosition(sf::Vector2f{x, y});
            bar.setFillColor(colorForBar(i));
            window.draw(bar);
        }
    }

    void Visualizer::drawStatistics()
    {
        sf::RectangleShape panel;
        panel.setPosition(sf::Vector2f{0.0F, 0.0F});
        panel.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), topPanelHeight));
        panel.setFillColor(sf::Color(28, 30, 34));
        window.draw(panel);

        if (!fontLoaded)
        {
            return;
        }

        std::ostringstream stats;
        stats << "Comparisons: " << comparisonCount
              << "   Swaps: " << swapCount
              << "   Size: " << values.size()
              << "   Time: " << std::fixed << std::setprecision(2) << getElapsedTime() << "s"
              << "   FPS: " << std::setprecision(1) << measuredFps
              << "   Delay: " << animationDelayMs << "ms"
              << "   Sound: " << (soundEnabled && soundLoaded ? "on" : "off");

        if (paused)
        {
            stats << "   Paused";
        }
        else if (restartRequested)
        {
            stats << "   Restart";
        }
        else if (randomizeRequested)
        {
            stats << "   Randomize";
        }
        else if (finished)
        {
            stats << "   Finished";
        }

#if SFML_VERSION_MAJOR >= 3
        sf::Text text(font, stats.str(), 18);
#else
        sf::Text text(stats.str(), font, 18);
#endif
        text.setFillColor(sf::Color::White);
        text.setPosition(sf::Vector2f{16.0F, 22.0F});
        window.draw(text);
    }

    void Visualizer::processPause()
    {
        while (paused && isOpen())
        {
            pollEvents();
            draw();
            window.display();
            updateFps();

            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
    }

    void Visualizer::updateFps()
    {
        ++framesThisSecond;

        const auto now = std::chrono::steady_clock::now();
        const auto elapsed = std::chrono::duration<double>(now - fpsWindowStart).count();

        if (elapsed >= 1.0)
        {
            measuredFps = static_cast<double>(framesThisSecond) / elapsed;
            framesThisSecond = 0;
            fpsWindowStart = now;
        }
    }

    void Visualizer::loadFont()
    {
        static constexpr std::array<const char*, 5> candidates = {
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
            "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
            "/usr/share/fonts/truetype/freefont/FreeSans.ttf",
            "/usr/share/fonts/TTF/DejaVuSans.ttf",
            "/usr/share/fonts/dejavu/DejaVuSans.ttf"
        };

        for (const char* path : candidates)
        {
            if (std::filesystem::exists(path) && loadFontFromFile(font, path))
            {
                fontLoaded = true;
                return;
            }
        }
    }

    void Visualizer::loadSounds()
    {
        const std::vector<std::int16_t> compareSamples = makeTone(660.0F, 0.025F, 0.20F);
        const std::vector<std::int16_t> swapSamples = makeTone(330.0F, 0.045F, 0.28F);

        if (!loadMonoSamples(compareBuffer, compareSamples) || !loadMonoSamples(swapBuffer, swapSamples))
        {
            soundLoaded = false;
            soundEnabled = false;
            return;
        }

        compareSound.emplace(compareBuffer);
        swapSound.emplace(swapBuffer);
        compareSound->setVolume(35.0F);
        swapSound->setVolume(45.0F);
        soundLoaded = true;
    }

    void Visualizer::playCompareSound()
    {
        if (!soundEnabled || !soundLoaded || !compareSound)
        {
            return;
        }

        compareSound->stop();
        compareSound->play();
    }

    void Visualizer::playSwapSound()
    {
        if (!soundEnabled || !soundLoaded || !swapSound)
        {
            return;
        }

        swapSound->stop();
        swapSound->play();
    }

    sf::Color Visualizer::colorForBar(const std::size_t index) const
    {
        if (finished)
        {
            return sf::Color(78, 220, 120);
        }

        const auto barIndex = static_cast<int>(index);

        if (barIndex == currentA || barIndex == currentB)
        {
            return swapped ? sf::Color(255, 210, 64) : sf::Color(235, 72, 72);
        }

        return sf::Color(238, 238, 238);
    }
}
