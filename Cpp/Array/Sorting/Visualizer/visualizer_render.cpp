#include "visualizer.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <sstream>

namespace Sorting
{
    void Visualizer::draw()
    {
        window.clear(sf::Color(18, 18, 20));
        drawBars();
        drawStatistics();
    }

    void Visualizer::drawAlgorithmSelection(
        const std::size_t arraySize,
        const int delayMilliseconds,
        const int minValue,
        const int maxValue,
        const bool randomizeSize,
        const bool soundEnabled,
        const std::string& arraySizeText,
        const bool editingArraySize)
    {
        static constexpr std::array<const char*, 5> algorithmNames = {
            "1  Insertion Sort", "2  Selection Sort", "3  Bubble Sort", "4  Merge Sort", "5  Quick Sort"};
        window.clear(sf::Color(18, 18, 20));

        if (fontLoaded)
        {
#if SFML_VERSION_MAJOR >= 3
            sf::Text title(font, "Choose a sorting algorithm", 32);
            sf::Text settings(font, "Settings", 26);
            sf::Text sizeLabel(font, "Array size", 20);
            sf::Text delayLabel(font, "Animation delay", 20);
            sf::Text minLabel(font, "Minimum value", 20);
            sf::Text maxLabel(font, "Maximum value", 20);
            sf::Text sizeValue(font, arraySizeText + (editingArraySize ? "_" : ""), 22);
            sf::Text delayValue(font, std::to_string(delayMilliseconds) + " ms", 18);
#else
            sf::Text title("Choose a sorting algorithm", font, 32);
            sf::Text settings("Settings", font, 26);
            sf::Text sizeLabel("Array size", font, 20);
            sf::Text delayLabel("Animation delay", font, 20);
            sf::Text minLabel("Minimum value", font, 20);
            sf::Text maxLabel("Maximum value", font, 20);
            sf::Text sizeValue(arraySizeText + (editingArraySize ? "_" : ""), font, 22);
            sf::Text delayValue(std::to_string(delayMilliseconds) + " ms", font, 18);
#endif
            title.setPosition({40.0F, 55.0F});
            settings.setPosition({520.0F, 55.0F});
            sizeLabel.setPosition({520.0F, 175.0F});
            delayLabel.setPosition({520.0F, 390.0F});
            minLabel.setPosition({520.0F, 490.0F});
            maxLabel.setPosition({520.0F, 590.0F});
            sizeValue.setPosition({540.0F, 230.0F});
            delayValue.setPosition({1040.0F, 432.0F});
            for (sf::Text* label : {&title, &settings, &sizeLabel, &delayLabel, &minLabel, &maxLabel, &delayValue})
            {
                label->setFillColor(sf::Color::White);
                window.draw(*label);
            }
        }

        sf::RectangleShape input;
        input.setPosition({520.0F, 215.0F});
        input.setSize({420.0F, 60.0F});
        input.setFillColor(sf::Color(35, 38, 44));
        input.setOutlineThickness(2.0F);
        input.setOutlineColor(editingArraySize ? sf::Color(100, 190, 255) : sf::Color(75, 80, 90));
        window.draw(input);

        if (fontLoaded)
        {
    #if SFML_VERSION_MAJOR >= 3
            sf::Text sizeValue(font, arraySizeText + (editingArraySize ? "_" : ""), 22);
            sf::Text arrayRange(font, "10", 16);
            sf::Text arrayMaximum(font, "200 elements", 16);
    #else
            sf::Text sizeValue(arraySizeText + (editingArraySize ? "_" : ""), font, 22);
            sf::Text arrayRange("10", font, 16);
            sf::Text arrayMaximum("200 elements", font, 16);
    #endif
            sizeValue.setPosition({540.0F, 230.0F});
            arrayRange.setPosition({592.0F, 372.0F});
            arrayMaximum.setPosition({1000.0F, 372.0F});
            sizeValue.setFillColor(sf::Color::White);
            arrayRange.setFillColor(sf::Color(180, 185, 195));
            arrayMaximum.setFillColor(sf::Color(180, 185, 195));
            window.draw(sizeValue);
            window.draw(arrayRange);
            window.draw(arrayMaximum);
        }

        const auto drawSlider = [&](const float y, const float normalized)
        {
            sf::RectangleShape track;
            track.setPosition({600.0F, y});
            track.setSize({400.0F, 8.0F});
            track.setFillColor(sf::Color(75, 80, 90));
            window.draw(track);

            sf::CircleShape knob(10.0F);
            knob.setOrigin({10.0F, 10.0F});
            knob.setPosition({600.0F + normalized * 400.0F, y + 4.0F});
            knob.setFillColor(sf::Color(100, 190, 255));
            window.draw(knob);
        };
        drawSlider(355.0F, static_cast<float>(arraySize - 10) / 190.0F);
        drawSlider(455.0F, static_cast<float>(delayMilliseconds) / 200.0F);
        drawSlider(555.0F, static_cast<float>(minValue) / 200.0F);
        drawSlider(655.0F, static_cast<float>(maxValue) / 255.0F);

        if (fontLoaded)
        {
    #if SFML_VERSION_MAJOR >= 3
            sf::Text delayMinimum(font, "0 ms", 16);
            sf::Text delayMaximum(font, "200 ms", 16);
    #else
            sf::Text delayMinimum("0 ms", font, 16);
            sf::Text delayMaximum("200 ms", font, 16);
    #endif
            delayMinimum.setPosition({592.0F, 472.0F});
            delayMaximum.setPosition({1000.0F, 472.0F});
            delayMinimum.setFillColor(sf::Color(180, 185, 195));
            delayMaximum.setFillColor(sf::Color(180, 185, 195));
            window.draw(delayMinimum);
            window.draw(delayMaximum);

#if SFML_VERSION_MAJOR >= 3
            sf::Text minValueText(font, std::to_string(minValue), 16);
            sf::Text maxValueText(font, std::to_string(maxValue), 16);
#else
            sf::Text minValueText(std::to_string(minValue), font, 16);
            sf::Text maxValueText(std::to_string(maxValue), font, 16);
#endif
            minValueText.setPosition({1040.0F, 532.0F});
            maxValueText.setPosition({1040.0F, 632.0F});
            minValueText.setFillColor(sf::Color::White);
            maxValueText.setFillColor(sf::Color::White);
            window.draw(minValueText);
            window.draw(maxValueText);
        }

        sf::RectangleShape randomButton;
        randomButton.setPosition({520.0F, 735.0F});
        randomButton.setSize({220.0F, 55.0F});
        randomButton.setFillColor(randomizeSize ? sf::Color(48, 130, 90) : sf::Color(48, 92, 140));
        window.draw(randomButton);

        sf::RectangleShape soundButton;
        soundButton.setPosition({760.0F, 735.0F});
        soundButton.setSize({200.0F, 55.0F});
        soundButton.setFillColor(soundEnabled ? sf::Color(48, 130, 90) : sf::Color(90, 70, 70));
        window.draw(soundButton);

        if (fontLoaded)
        {
#if SFML_VERSION_MAJOR >= 3
            sf::Text randomLabel(font, randomizeSize ? "Random size: ON" : "Random size: OFF", 17);
            sf::Text soundLabel(font, soundEnabled ? "Sound: ON" : "Sound: OFF", 17);
#else
            sf::Text randomLabel(randomizeSize ? "Random size: ON" : "Random size: OFF", font, 17);
            sf::Text soundLabel(soundEnabled ? "Sound: ON" : "Sound: OFF", font, 17);
#endif
            randomLabel.setPosition({542.0F, 752.0F});
            soundLabel.setPosition({795.0F, 752.0F});
            randomLabel.setFillColor(sf::Color::White);
            soundLabel.setFillColor(sf::Color::White);
            window.draw(randomLabel);
            window.draw(soundLabel);
        }

        for (std::size_t i = 0; i < algorithmNames.size(); ++i)
        {
            sf::RectangleShape button;
            button.setPosition({40.0F, 150.0F + static_cast<float>(i) * 80.0F});
            button.setSize({420.0F, 64.0F});
            button.setFillColor(sf::Color(48, 92, 140));
            button.setOutlineThickness(1.0F);
            button.setOutlineColor(sf::Color(100, 150, 200));
            window.draw(button);

            if (fontLoaded)
            {
#if SFML_VERSION_MAJOR >= 3
                sf::Text label(font, algorithmNames[i], 24);
#else
                sf::Text label(algorithmNames[i], font, 24);
#endif
                label.setFillColor(sf::Color::White);
                label.setPosition({64.0F, 167.0F + static_cast<float>(i) * 80.0F});
                window.draw(label);
            }
        }
    }

    void Visualizer::drawBars()
    {
        if (values.empty()) return;

        const sf::Vector2u windowSize = window.getSize();
        const auto maxValue = static_cast<float>(*std::max_element(values.begin(), values.end()));
        const float drawableHeight = std::max(1.0F, static_cast<float>(windowSize.y) - topPanelHeight - 16.0F);
        const float barAreaBottom = static_cast<float>(windowSize.y) - 8.0F;
        const float barSlotWidth = static_cast<float>(windowSize.x) / static_cast<float>(values.size());
        const float barWidth = std::max(1.0F, barSlotWidth - 1.0F);
        sf::RectangleShape bar;

        for (std::size_t i = 0; i < values.size(); ++i)
        {
            const float normalized = maxValue <= 0.0F ? 0.0F : static_cast<float>(values[i]) / maxValue;
            const float height = std::max(2.0F, std::floor(normalized * drawableHeight));
            const float y = std::max(topPanelHeight, barAreaBottom - height);
            bar.setSize({barWidth, barAreaBottom - y});
            bar.setPosition({static_cast<float>(i) * barSlotWidth, y});
            bar.setFillColor(colorForBar(i));
            window.draw(bar);
        }
    }

    void Visualizer::drawStatistics()
    {
        sf::RectangleShape panel;
        panel.setSize({static_cast<float>(window.getSize().x), topPanelHeight});
        panel.setFillColor(sf::Color(28, 30, 34));
        window.draw(panel);
        if (!fontLoaded) return;

        std::ostringstream stats;
        stats << "Comparisons: " << comparisonCount << "   Swaps: " << swapCount
              << "   Size: " << values.size() << "   Time: " << std::fixed << std::setprecision(2)
              << getElapsedTime() << "s   FPS: " << std::setprecision(1) << measuredFps
              << "   Delay: " << animationDelayMs << "ms   Sound: "
              << (soundEnabled && soundLoaded ? "on" : "off");
        if (paused) stats << "   Paused";
        else if (restartRequested) stats << "   Restart";
        else if (randomizeRequested) stats << "   Randomize";
        else if (finished) stats << "   Finished";

#if SFML_VERSION_MAJOR >= 3
        sf::Text text(font, stats.str(), 18);
#else
        sf::Text text(stats.str(), font, 18);
#endif
        text.setFillColor(sf::Color::White);
        text.setPosition({16.0F, 22.0F});
        window.draw(text);

        if (finished)
        {
            sf::RectangleShape backButton;
            backButton.setPosition({static_cast<float>(window.getSize().x) - 190.0F, 14.0F});
            backButton.setSize({174.0F, 44.0F});
            backButton.setFillColor(sf::Color(48, 92, 140));
            backButton.setOutlineThickness(1.0F);
            backButton.setOutlineColor(sf::Color(100, 150, 200));
            window.draw(backButton);
#if SFML_VERSION_MAJOR >= 3
            sf::Text backLabel(font, "Back to menu", 16);
#else
            sf::Text backLabel("Back to menu", font, 16);
#endif
            backLabel.setPosition({static_cast<float>(window.getSize().x) - 174.0F, 25.0F});
            backLabel.setFillColor(sf::Color::White);
            window.draw(backLabel);
        }
    }
}
