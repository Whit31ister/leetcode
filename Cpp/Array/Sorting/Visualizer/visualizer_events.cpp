#include "visualizer.h"

#include <algorithm>
#include <chrono>
#include <string>
#include <thread>

namespace Sorting
{
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
                window.setView(sf::View(sf::FloatRect({0.0F, 0.0F}, {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)})));
            }
            else if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::Escape) window.close();
                else if (key->code == sf::Keyboard::Key::Space) paused = !paused;
                else if (key->code == sf::Keyboard::Key::R) { restartRequested = true; paused = false; }
                else if (key->code == sf::Keyboard::Key::N) { randomizeRequested = true; paused = false; }
                else if (key->code == sf::Keyboard::Key::M) soundEnabled = !soundEnabled;
                else if (key->code == sf::Keyboard::Key::B && finished) backRequested = true;
                else if (key->code == sf::Keyboard::Key::Up || key->code == sf::Keyboard::Key::Add) setDelay(animationDelayMs - 5);
                else if (key->code == sf::Keyboard::Key::Down || key->code == sf::Keyboard::Key::Subtract) setDelay(animationDelayMs + 5);
            }
            else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (finished && mouse->button == sf::Mouse::Button::Left && mouse->position.x >= static_cast<int>(window.getSize().x) - 190 && mouse->position.x <= static_cast<int>(window.getSize().x) - 16 && mouse->position.y >= 14 && mouse->position.y <= 58)
                {
                    backRequested = true;
                }
            }
        }
#else
        sf::Event event {};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            else if (event.type == sf::Event::Resized)
            {
                window.setView(sf::View(sf::FloatRect(0.0F, 0.0F, static_cast<float>(event.size.width), static_cast<float>(event.size.height))));
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape) window.close();
                else if (event.key.code == sf::Keyboard::Space) paused = !paused;
                else if (event.key.code == sf::Keyboard::R) { restartRequested = true; paused = false; }
                else if (event.key.code == sf::Keyboard::N) { randomizeRequested = true; paused = false; }
                else if (event.key.code == sf::Keyboard::M) soundEnabled = !soundEnabled;
                else if (event.key.code == sf::Keyboard::B && finished) backRequested = true;
                else if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Add) setDelay(animationDelayMs - 5);
                else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::Subtract) setDelay(animationDelayMs + 5);
            }
            else if (event.type == sf::Event::MouseButtonPressed && finished && event.mouseButton.button == sf::Mouse::Left && event.mouseButton.x >= static_cast<int>(window.getSize().x) - 190 && event.mouseButton.x <= static_cast<int>(window.getSize().x) - 16 && event.mouseButton.y >= 14 && event.mouseButton.y <= 58)
            {
                backRequested = true;
            }
        }
#endif
    }

    int Visualizer::selectAlgorithm(
        std::size_t& arraySize,
        int& delayMilliseconds,
        int& minValue,
        int& maxValue,
        bool& randomizeSize,
        bool& soundEnabled)
    {
        constexpr float firstButtonY = 150.0F;
        constexpr float buttonHeight = 64.0F;
        constexpr float buttonGap = 16.0F;
        constexpr float sliderStartX = 980.0F;
        constexpr float sliderEndX = 1380.0F;
        std::string arraySizeText = std::to_string(arraySize);
        bool editingArraySize = false;
        bool draggingArraySize = false;
        bool draggingDelay = false;
        bool draggingMinValue = false;
        bool draggingMaxValue = false;

        const auto updateArraySize = [&]()
        {
            try
            {
                arraySize = std::clamp<std::size_t>(std::stoul(arraySizeText), 10, 200);
                arraySizeText = std::to_string(arraySize);
            }
            catch (...)
            {
                arraySize = 40;
                arraySizeText = "40";
            }
        };

        const auto updateSlider = [&](const float x, const float y)
        {
            const auto normalized = std::clamp((x - sliderStartX) / (sliderEndX - sliderStartX), 0.0F, 1.0F);
            if (draggingArraySize && y >= 325.0F && y <= 385.0F)
            {
                arraySize = static_cast<std::size_t>(10 + normalized * 190.0F);
                arraySizeText = std::to_string(arraySize);
            }
            if (draggingDelay && y >= 425.0F && y <= 485.0F)
            {
                delayMilliseconds = static_cast<int>(normalized * 200.0F);
            }
            if (draggingMinValue && y >= 525.0F && y <= 585.0F)
            {
                minValue = std::min(static_cast<int>(normalized * 200.0F), maxValue - 1);
            }
            if (draggingMaxValue && y >= 625.0F && y <= 685.0F)
            {
                maxValue = std::max(minValue + 1, static_cast<int>(normalized * 255.0F));
            }
        };

        while (isOpen())
        {
#if SFML_VERSION_MAJOR >= 3
            while (const auto event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>()) window.close();
                else if (const auto* key = event->getIf<sf::Event::KeyPressed>())
                {
                    if (key->code == sf::Keyboard::Key::Escape) window.close();
                    else if (key->code == sf::Keyboard::Key::Backspace && editingArraySize && !arraySizeText.empty()) arraySizeText.pop_back();
                    else if (key->code == sf::Keyboard::Key::Enter && editingArraySize) { updateArraySize(); editingArraySize = false; }
                    else if (!editingArraySize)
                    {
                        const auto number = static_cast<int>(key->code) - static_cast<int>(sf::Keyboard::Key::Num1) + 1;
                        if (number >= 1 && number <= 9) return number;
                        if (key->code == sf::Keyboard::Key::Num0) return 10;
                    }
                }
                else if (const auto* text = event->getIf<sf::Event::TextEntered>())
                {
                    if (editingArraySize && text->unicode >= '0' && text->unicode <= '9' && arraySizeText.size() < 3) arraySizeText += static_cast<char>(text->unicode);
                }
                else if (const auto* mouse = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mouse->button != sf::Mouse::Button::Left) continue;
                    const float x = static_cast<float>(mouse->position.x);
                    const float y = static_cast<float>(mouse->position.y);
                    for (int index = 0; index < 10; ++index)
                    {
                        const float buttonX = index < 5 ? 40.0F : 430.0F;
                        const float buttonY = firstButtonY + static_cast<float>(index % 5) * (buttonHeight + buttonGap);
                        if (x >= buttonX && x <= buttonX + 350.0F && y >= buttonY && y <= buttonY + buttonHeight) { updateArraySize(); return index + 1; }
                    }
                    if (x >= 860.0F && x <= 1320.0F && y >= 215.0F && y <= 275.0F) editingArraySize = true;
                    else if (x >= sliderStartX - 20.0F && x <= sliderEndX + 20.0F && y >= 340.0F && y <= 370.0F)
                    {
                        draggingArraySize = true;
                        updateSlider(x, y);
                    }
                    else if (x >= sliderStartX - 20.0F && x <= sliderEndX + 20.0F && y >= 440.0F && y <= 470.0F)
                    {
                        draggingDelay = true;
                        updateSlider(x, y);
                    }
                    else if (x >= sliderStartX - 20.0F && x <= sliderEndX + 20.0F && y >= 540.0F && y <= 570.0F)
                    {
                        draggingMinValue = true;
                        updateSlider(x, y);
                    }
                    else if (x >= sliderStartX - 20.0F && x <= sliderEndX + 20.0F && y >= 640.0F && y <= 670.0F)
                    {
                        draggingMaxValue = true;
                        updateSlider(x, y);
                    }
                    else if (x >= 860.0F && x <= 1080.0F && y >= 735.0F && y <= 790.0F)
                    {
                        randomizeSize = !randomizeSize;
                    }
                    else if (x >= 1100.0F && x <= 1300.0F && y >= 735.0F && y <= 790.0F)
                    {
                        soundEnabled = !soundEnabled;
                    }
                }
                else if (const auto* mouse = event->getIf<sf::Event::MouseButtonReleased>())
                {
                    if (mouse->button == sf::Mouse::Button::Left)
                    {
                        draggingArraySize = false;
                        draggingDelay = false;
                        draggingMinValue = false;
                        draggingMaxValue = false;
                    }
                }
                else if (const auto* mouse = event->getIf<sf::Event::MouseMoved>())
                {
                    updateSlider(static_cast<float>(mouse->position.x), static_cast<float>(mouse->position.y));
                }
            }
#else
            sf::Event event {};
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) window.close();
                else if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape) window.close();
                    else if (event.key.code == sf::Keyboard::BackSpace && editingArraySize && !arraySizeText.empty()) arraySizeText.pop_back();
                    else if (event.key.code == sf::Keyboard::Return && editingArraySize) { updateArraySize(); editingArraySize = false; }
                    else if (!editingArraySize && event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9) return static_cast<int>(event.key.code - sf::Keyboard::Num1) + 1;
                    else if (!editingArraySize && event.key.code == sf::Keyboard::Num0) return 10;
                }
                else if (event.type == sf::Event::TextEntered && editingArraySize && event.text.unicode >= '0' && event.text.unicode <= '9' && arraySizeText.size() < 3) arraySizeText += static_cast<char>(event.text.unicode);
                else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    const float x = static_cast<float>(event.mouseButton.x);
                    const float y = static_cast<float>(event.mouseButton.y);
                    for (int index = 0; index < 10; ++index)
                    {
                        const float buttonX = index < 5 ? 40.0F : 430.0F;
                        const float buttonY = firstButtonY + static_cast<float>(index % 5) * (buttonHeight + buttonGap);
                        if (x >= buttonX && x <= buttonX + 350.0F && y >= buttonY && y <= buttonY + buttonHeight) { updateArraySize(); return index + 1; }
                    }
                    if (x >= 860.0F && x <= 1320.0F && y >= 215.0F && y <= 275.0F) editingArraySize = true;
                    else if (x >= sliderStartX - 20.0F && x <= sliderEndX + 20.0F && y >= 340.0F && y <= 370.0F) { draggingArraySize = true; updateSlider(x, y); }
                    else if (x >= sliderStartX - 20.0F && x <= sliderEndX + 20.0F && y >= 440.0F && y <= 470.0F) { draggingDelay = true; updateSlider(x, y); }
                    else if (x >= sliderStartX - 20.0F && x <= sliderEndX + 20.0F && y >= 540.0F && y <= 570.0F) { draggingMinValue = true; updateSlider(x, y); }
                    else if (x >= sliderStartX - 20.0F && x <= sliderEndX + 20.0F && y >= 640.0F && y <= 670.0F) { draggingMaxValue = true; updateSlider(x, y); }
                    else if (x >= 860.0F && x <= 1080.0F && y >= 735.0F && y <= 790.0F) randomizeSize = !randomizeSize;
                    else if (x >= 1100.0F && x <= 1300.0F && y >= 735.0F && y <= 790.0F) soundEnabled = !soundEnabled;
                }
                else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
                {
                    draggingArraySize = false;
                    draggingDelay = false;
                    draggingMinValue = false;
                    draggingMaxValue = false;
                }
                else if (event.type == sf::Event::MouseMoved)
                {
                    updateSlider(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y));
                }
            }
#endif
            drawAlgorithmSelection(arraySize, delayMilliseconds, minValue, maxValue, randomizeSize, soundEnabled, arraySizeText, editingArraySize);
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }
        return 0;
    }
}
