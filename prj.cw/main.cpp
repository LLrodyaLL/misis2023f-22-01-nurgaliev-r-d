#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include "image.h"



struct App {
    sf::RenderWindow window;

    sf::Vector2f translate;
    sf::Vector2f mouseCoord;

    Image firstIm;
    Image secondIm;
    Image thirdIm;

    sf::Vector2f firstCursorPos;
    sf::Vector2f secondCursorPos;
    sf::Vector2f thirdCursorPos;

    float zoom;

    void constrainCursorToBounds(sf::Vector2f& cursorPos, const Image& image) {
        // Проверка и коррекция границ курсора внутри спрайта
        if (cursorPos.x < 0) {
            cursorPos.x = 0;
        }
        else if (cursorPos.x > image.internalTexture.getSize().x) {
            cursorPos.x = static_cast<float>(image.internalTexture.getSize().x);
        }

        if (cursorPos.y < 0) {
            cursorPos.y = 0;
        }
        else if (cursorPos.y > image.internalTexture.getSize().y) {
            cursorPos.y = static_cast<float>(image.internalTexture.getSize().y);
        }
    }

    App() : window(sf::VideoMode(1600, 800), "AstMarker"), zoom(1.0f) {

        firstIm.internalTexture.create(window.getSize().x / 3, window.getSize().y);
        secondIm.internalTexture.create(window.getSize().x / 3, window.getSize().y);
        thirdIm.internalTexture.create(window.getSize().x / 3, window.getSize().y);


        firstCursorPos = sf::Vector2f(window.getSize().x / 6, window.getSize().y / 2);
        secondCursorPos = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
        thirdCursorPos = sf::Vector2f(window.getSize().x * 5 / 6, window.getSize().y / 2);

    }

    void handleInput() {
        sf::Event event;
        while (window.pollEvent(event)) {
            ImGui::SFML::ProcessEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));

                firstIm.internalTexture.create(window.getSize().x / 3, window.getSize().y);
                secondIm.internalTexture.create(window.getSize().x / 3, window.getSize().y);
                thirdIm.internalTexture.create(window.getSize().x / 3, window.getSize().y);

            }
            else if (event.type == sf::Event::MouseWheelScrolled) {

                sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                auto oldZoom = zoom;
                // Масштабирование колёсиком мыши
                if (event.mouseWheelScroll.delta > 0) {
                    zoom *= 1.1f;
                }
                else {
                    zoom /= 1.1f;
                }
                auto centerX = firstIm.internalTexture.getSize().x / 2;
                auto centerY = firstIm.internalTexture.getSize().y / 2;
                sf::Vector2f temp(((centerX) * (oldZoom - zoom) / 2), ((centerY) * (oldZoom - zoom) / 2));
                translate = mousePosition - (mousePosition - translate) * (zoom / oldZoom);


            }
            else if (event.type == sf::Event::MouseMoved) {
                // Движение мыши
                sf::Vector2f newCoord(event.mouseMove.x, event.mouseMove.y);

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                sf::Vector2f mousePosFloat4Second(mousePosFloat.x - static_cast<float>(window.getSize().x) / 3.0f, mousePosFloat.y);

                // Проверка и коррекция границ курсоров
                constrainCursorToBounds(firstCursorPos, firstIm);
                constrainCursorToBounds(secondCursorPos, secondIm);
                constrainCursorToBounds(thirdCursorPos, thirdIm);

              
                if (mousePos.x > window.getSize().x / 3 && mousePos.x < window.getSize().x / 3 * 2) {
                    secondCursorPos.x = mousePosFloat.x - window.getSize().x / 3;
                    secondCursorPos.y = mousePosFloat.y;

                    sf::Vector2f localCursorPos = secondIm.sprite.getInverseTransform().transformPoint(secondCursorPos);
                    secondIm.cursor1_1.setPosition(localCursorPos.x - 6.6, localCursorPos.y);
                    secondIm.cursor1_2.setPosition(localCursorPos.x, localCursorPos.y - 6.6);
                }

                if ((mousePos.x < window.getSize().x / 3) and firstIm.is_opened and secondIm.is_opened) {
                    bool loopCompleted = true;
                    for (std::size_t i = 0; i < firstIm.drawPoints.size(); ++i) {
                        sf::Rect pointBounds = firstIm.drawPoints[i].getGlobalBounds();
                        sf::Vector2f pointSize(firstIm.sprite.getTransform().transformPoint(pointBounds.left, pointBounds.top));
                        pointBounds.left = pointSize.x;
                        pointBounds.top = pointSize.y;
                        if (pointBounds.contains(mousePosFloat)) {
                            firstIm.hoveredCircleIndex = static_cast<int>(i);
                            loopCompleted = false;
                            break;
                        }
                    }
                    if (loopCompleted) { firstIm.hoveredCircleIndex = -1; }
                }
                if (mousePos.x > window.getSize().x / 3 and mousePos.x < window.getSize().x / 3 * 2 and secondIm.is_opened) {
                    bool loopCompleted = true;
                    for (std::size_t i = 0; i < secondIm.drawPoints.size(); ++i) {
                        sf::Rect pointBounds = secondIm.drawPoints[i].getGlobalBounds();
                        sf::Vector2f pointSize(secondIm.sprite.getTransform().transformPoint(pointBounds.left, pointBounds.top));
                        pointBounds.left = pointSize.x;
                        pointBounds.top = pointSize.y;
                        if (pointBounds.contains(mousePosFloat4Second)) {
                            secondIm.hoveredCircleIndex = static_cast<int>(i);
                            loopCompleted = false;
                            break;
                        }
                    }
                    if (loopCompleted) { secondIm.hoveredCircleIndex = -1; }
                }

                if (firstIm.selectedCircleIndex != -1) {
                    firstIm.drawPoints[firstIm.selectedCircleIndex].setPosition(firstIm.sprite.getInverseTransform().transformPoint(mousePosFloat));

                }
                if (secondIm.selectedCircleIndex != -1) {
                    secondIm.drawPoints[secondIm.selectedCircleIndex].setPosition(secondIm.sprite.getInverseTransform().transformPoint(mousePosFloat4Second));
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    translate += newCoord - mouseCoord;
                }
                mouseCoord = newCoord;

                firstCursorPos = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                secondCursorPos = sf::Vector2f(event.mouseMove.x - window.getSize().x / 3, event.mouseMove.y);
                thirdCursorPos = sf::Vector2f(event.mouseMove.x - window.getSize().x / 3 * 2, event.mouseMove.y);

                
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                if ((mousePos.x < window.getSize().x / 3) and firstIm.is_opened and secondIm.is_opened) {
                    firstIm.selectedCircleIndex = firstIm.hoveredCircleIndex;
                    if (firstIm.selectedCircleIndex == -1) {
                        sf::CircleShape newCircle(10);
                        newCircle.setFillColor(sf::Color::Red);
                        newCircle.setPosition(firstIm.sprite.getInverseTransform().transformPoint(mousePosFloat));


                        secondIm.predictPoint(newCircle.getPosition(), firstIm);


                        firstIm.drawPoints.push_back(newCircle);
                    }
                }
                else if (mousePos.x > window.getSize().x / 3 and mousePos.x < window.getSize().x / 3 * 2 and secondIm.is_opened) {
                    mousePosFloat.x += -static_cast<float>(window.getSize().x) / 3.0f;
                    secondIm.selectedCircleIndex = secondIm.hoveredCircleIndex;
                    if (secondIm.selectedCircleIndex == -1) {
                        sf::CircleShape newCircle(10);
                        newCircle.setFillColor(sf::Color::Red);
                        newCircle.setPosition(secondIm.sprite.getInverseTransform().transformPoint(mousePosFloat));
                        firstIm.predictPoint(newCircle.getPosition(), secondIm);

                        secondIm.drawPoints.push_back(newCircle);
                        //
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (firstIm.selectedCircleIndex != -1 or secondIm.selectedCircleIndex != -1) {
                    firstIm.selectedCircleIndex = -1;
                    secondIm.selectedCircleIndex = -1;
                    thirdIm.genWarpImg(firstIm, secondIm);
                }
                // Сбрасываем индекс выбранного круга при отпускании кнопки мыши
//                firstIm.selectedCircleIndex = -1;
//                secondIm.selectedCircleIndex = -1;

            }
        }
    }


    void update() {
        ImGui::SFML::Update(window, sf::seconds(1.0f / 60.0f));


        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open Image 1")) firstIm.openImage();
                if (ImGui::MenuItem("Open Image 2")) secondIm.openImage();
                if (ImGui::MenuItem("Import a set of points", "CTRL+O", false, true));
                ImGui::Separator();
                if (ImGui::MenuItem("Save", "CTRL+S", false, true));
                ImGui::Separator();
                if (ImGui::MenuItem("Quit")) {
                    //TODO: Фунуция для выхода из программы
                }
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }


        ImGui::Begin("statusbar", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
        {
            ImGui::SetWindowPos(ImVec2(0.0f, window.getSize().y - 30.0f));
            ImGui::SetWindowSize(ImVec2(window.getSize().x, 30.0f));

            ImGui::Columns(6);
            ImGui::Text("win size: %d %d", window.getSize().x, window.getSize().y);
            ImGui::NextColumn();
            ImGui::Text("translate: %f %f", translate.x, translate.y);
            ImGui::NextColumn();
            ImGui::Text("zoom: %f", zoom);
            ImGui::NextColumn();
            ImGui::Text("mouse: %d %d", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            ImGui::NextColumn();
            ImGui::Text("1 hoverID: %d", firstIm.hoveredCircleIndex);
            ImGui::NextColumn();
            ImGui::Text("2 hoverID: %d", secondIm.hoveredCircleIndex);
        }
        ImGui::End();

    }

    void render() {
        window.clear();
        if (firstIm.is_opened) {
            firstIm.internalTexture.clear();
            sf::Sprite internalSprite;
            internalSprite.setTexture(firstIm.internalTexture.getTexture());
            firstIm.sprite.setPosition(translate);
            firstIm.sprite.setScale(zoom, zoom);
            firstIm.internalTexture.draw(firstIm.sprite);

            for (std::size_t i = 0; i < firstIm.drawPoints.size(); ++i) {
                sf::CircleShape tempCircle = firstIm.drawPoints[i];
                tempCircle.setPosition(firstIm.sprite.getTransform().transformPoint(firstIm.drawPoints[i].getPosition()));
                if (firstIm.hoveredCircleIndex == i or secondIm.hoveredCircleIndex == i)tempCircle.setFillColor(sf::Color::Blue);
                firstIm.internalTexture.draw(tempCircle);
            }

            sf::RectangleShape cursor1_1(sf::Vector2f(18, 5));
            cursor1_1.setFillColor(sf::Color::Green);
            cursor1_1.setPosition(firstCursorPos.x - 6.6, firstCursorPos.y);
            window.draw(cursor1_1);

            sf::RectangleShape cursor1_2(sf::Vector2f(5, 18));
            cursor1_2.setFillColor(sf::Color::Green);
            cursor1_2.setPosition(firstCursorPos.x, firstCursorPos.y - 6.6);
            window.draw(cursor1_2);

            firstIm.internalTexture.display();
            window.draw(internalSprite);
        }
        if (secondIm.is_opened) {
            secondIm.internalTexture.clear();
            sf::Sprite internalSprite;
            internalSprite.setTexture(secondIm.internalTexture.getTexture());
            internalSprite.move(window.getSize().x / 3, 0);
            secondIm.sprite.setPosition(translate);
            secondIm.sprite.setScale(zoom, zoom);

            secondIm.internalTexture.draw(secondIm.sprite);

            for (std::size_t i = 0; i < secondIm.drawPoints.size(); ++i) {
                sf::CircleShape tempCircle = secondIm.drawPoints[i];
                tempCircle.setPosition(secondIm.sprite.getTransform().transformPoint(secondIm.drawPoints[i].getPosition()));
                if (firstIm.hoveredCircleIndex == i or secondIm.hoveredCircleIndex == i)tempCircle.setFillColor(sf::Color::Blue);
                secondIm.internalTexture.draw(tempCircle);
            }

            sf::RectangleShape cursor2_1(sf::Vector2f(18, 5));
            cursor2_1.setFillColor(sf::Color::Green);
            cursor2_1.setPosition(secondCursorPos.x - 6.6, secondCursorPos.y);
            constrainCursorToBounds(secondCursorPos, secondIm);
            window.draw(cursor2_1);

            sf::RectangleShape cursor2_2(sf::Vector2f(5, 18));
            cursor2_2.setFillColor(sf::Color::Green);
            cursor2_2.setPosition(secondCursorPos.x, secondCursorPos.y - 6.6);
            constrainCursorToBounds(secondCursorPos, secondIm);
            window.draw(cursor2_2);

            secondIm.internalTexture.display();
            window.draw(internalSprite);
        }
        if (thirdIm.is_opened) {
            thirdIm.internalTexture.clear();
            sf::Sprite internalSprite;
            internalSprite.setTexture(thirdIm.internalTexture.getTexture());
            internalSprite.move(window.getSize().x / 3 * 2, 0);
            thirdIm.sprite.setPosition(translate);
            thirdIm.sprite.setScale(zoom, zoom);
            thirdIm.internalTexture.draw(thirdIm.sprite);

            sf::RectangleShape cursor3_1(sf::Vector2f(18, 5));
            cursor3_1.setFillColor(sf::Color::Green);
            cursor3_1.setPosition(thirdCursorPos.x - 6.6, thirdCursorPos.y);
            constrainCursorToBounds(thirdCursorPos, thirdIm);
            window.draw(cursor3_1);

            sf::RectangleShape cursor3_2(sf::Vector2f(5, 18));
            cursor3_2.setFillColor(sf::Color::Green);
            cursor3_2.setPosition(thirdCursorPos.x, thirdCursorPos.y - 6.6);
            constrainCursorToBounds(thirdCursorPos, thirdIm);
            window.draw(cursor3_2);

            thirdIm.internalTexture.display();
            window.draw(internalSprite);
        }


        ImGui::SFML::Render(window);
        window.display();

    }

    void run() {
        ImGui::SFML::Init(window);
        while (window.isOpen()) {
            handleInput();
            update();
            render();

        }
        ImGui::SFML::Shutdown();
    }
};

int main() {
    App app;
    app.run();

    return 0;
}
