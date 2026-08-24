#include "visualizer.h"

#include <algorithm>
#include <chrono>
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

        double elapsedSecondsSince(const std::chrono::steady_clock::time_point& start)
        {
            return std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count();
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
        finishedElapsedTime = elapsedSecondsSince(startTime);
        currentA = -1;
        currentB = -1;
        swapped = false;

        while (isOpen() && !restartRequested && !randomizeRequested && !backRequested)
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
        finishedElapsedTime = 0.0;
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

    bool Visualizer::consumeBackRequest()
    {
        const bool requested = backRequested;
        backRequested = false;
        return requested;
    }

    std::uint64_t Visualizer::getComparisonCount() const { return comparisonCount; }
    std::uint64_t Visualizer::getSwapCount() const { return swapCount; }

    double Visualizer::getElapsedTime() const
    {
        return finished ? finishedElapsedTime : elapsedSecondsSince(startTime);
    }

    double Visualizer::getFps() const { return measuredFps; }
    int Visualizer::getDelay() const { return animationDelayMs; }
    std::size_t Visualizer::getArraySize() const { return values.size(); }

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
}
