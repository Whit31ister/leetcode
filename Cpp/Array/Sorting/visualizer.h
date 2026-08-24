#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <cstdint>
#include <optional>
#include <vector>

namespace Sorting
{

    class Visualizer
    {
    public:
        Visualizer(
            int width = 1200,
            int height = 800,
            int fps = 60);

        void compare(int i,int j);

        void swap(int i,int j);

        void update(const std::vector<int>& arr);

        void finish();

        [[nodiscard]] bool isOpen() const;

        void pollEvents();

        void setDelay(int milliseconds);

        void setSoundEnabled(bool enabled);

        void resetStatistics();

        [[nodiscard]] bool shouldStop() const;

        [[nodiscard]] bool consumeRestartRequest();

        [[nodiscard]] bool consumeRandomizeRequest();

        [[nodiscard]] std::uint64_t getComparisonCount() const;

        [[nodiscard]] std::uint64_t getSwapCount() const;

        [[nodiscard]] double getElapsedTime() const;

        [[nodiscard]] double getFps() const;

        [[nodiscard]] int getDelay() const;

        [[nodiscard]] std::size_t getArraySize() const;

    private:
        void draw();

        void drawBars();

        void drawStatistics();

        void processPause();

        void updateFps();

        void loadFont();

        void loadSounds();

        void playCompareSound();

        void playSwapSound();

        [[nodiscard]] sf::Color colorForBar(std::size_t index) const;

        sf::RenderWindow window;
        sf::Font font;
        bool fontLoaded = false;

        sf::SoundBuffer compareBuffer;
        sf::SoundBuffer swapBuffer;
        std::optional<sf::Sound> compareSound;
        std::optional<sf::Sound> swapSound;
        bool soundEnabled = true;
        bool soundLoaded = false;

        std::vector<int> values;

        int currentA = -1;
        int currentB = -1;

        bool swapped = false;
        bool finished = false;
        bool paused = false;
        bool restartRequested = false;
        bool randomizeRequested = false;

        int animationDelayMs = 15;
        int targetFps = 60;

        std::uint64_t comparisonCount = 0;
        std::uint64_t swapCount = 0;
        double measuredFps = 0.0;
        unsigned int framesThisSecond = 0;

        std::chrono::steady_clock::time_point startTime;
        std::chrono::steady_clock::time_point fpsWindowStart;

        static constexpr float topPanelHeight = 72.0F;

    };

}
