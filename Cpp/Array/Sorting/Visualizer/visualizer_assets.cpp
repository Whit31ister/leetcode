#include "visualizer.h"

#include <SFML/Config.hpp>

#include <array>
#include <cmath>
#include <filesystem>
#include <limits>

namespace Sorting
{
    namespace
    {
        bool loadFontFromFile(sf::Font& font, const std::filesystem::path& path)
        {
#if SFML_VERSION_MAJOR >= 3
            return font.openFromFile(path);
#else
            return font.loadFromFile(path.string());
#endif
        }

        std::vector<std::int16_t> makeTone(const float frequency, const float durationSeconds, const float volume)
        {
            constexpr unsigned int sampleRate = 44100;
            constexpr float pi = 3.14159265358979323846F;
            const auto sampleCount = static_cast<std::size_t>(sampleRate * durationSeconds);
            std::vector<std::int16_t> samples(sampleCount);
            for (std::size_t i = 0; i < sampleCount; ++i)
            {
                const float time = static_cast<float>(i) / static_cast<float>(sampleRate);
                const float fade = 1.0F - static_cast<float>(i) / static_cast<float>(sampleCount);
                samples[i] = static_cast<std::int16_t>(std::sin(2.0F * pi * frequency * time) * fade * volume * static_cast<float>(std::numeric_limits<std::int16_t>::max()));
            }
            return samples;
        }

        bool loadMonoSamples(sf::SoundBuffer& buffer, const std::vector<std::int16_t>& samples)
        {
#if SFML_VERSION_MAJOR >= 3
            return buffer.loadFromSamples(samples.data(), static_cast<std::uint64_t>(samples.size()), 1, 44100, {sf::SoundChannel::Mono});
#else
            return buffer.loadFromSamples(samples.data(), static_cast<sf::Uint64>(samples.size()), 1, 44100);
#endif
        }
    }

    void Visualizer::loadFont()
    {
        static constexpr std::array<const char*, 7> candidates = {
            "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
            "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
            "/usr/share/fonts/truetype/freefont/FreeSans.ttf",
            "/usr/share/fonts/TTF/DejaVuSans.ttf",
            "/usr/share/fonts/dejavu/DejaVuSans.ttf",
            "/usr/share/fonts/abattis-cantarell-fonts/Cantarell-Regular.otf",
            "/usr/share/fonts/aajohan-comfortaa-fonts/Comfortaa-Regular.otf"};

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
        if (!loadMonoSamples(compareBuffer, makeTone(660.0F, 0.025F, 0.20F)) || !loadMonoSamples(swapBuffer, makeTone(330.0F, 0.045F, 0.28F)))
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
        if (soundEnabled && soundLoaded && compareSound) compareSound->play();
    }

    void Visualizer::playSwapSound()
    {
        if (soundEnabled && soundLoaded && swapSound) swapSound->play();
    }

    sf::Color Visualizer::colorForBar(const std::size_t index) const
    {
        if (static_cast<int>(index) == currentA || static_cast<int>(index) == currentB)
        {
            return swapped ? sf::Color(255, 140, 70) : sf::Color(100, 190, 255);
        }
        if (finished) return sf::Color(90, 190, 120);
        return sf::Color(70, 120, 190);
    }
}
