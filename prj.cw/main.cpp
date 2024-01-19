#include <SFML/Graphics.hpp>
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include "image.h"

/**
 * @struct App
 * @brief Структура приложения, управляющая основным окном и обрабатывающая ввод пользователя.
 */
struct App {
    sf::RenderWindow window; /**< Окно приложения. */

    sf::Vector2f translate; /**< Вектор смещения. */
    sf::Vector2f mouseCoord; /**< Координаты мыши. */

    Image firstIm; /**< Первое изображение. */
    Image secondIm; /**< Второе изображение. */
    Image thirdIm; /**< Третье изображение. */

    sf::Vector2f firstCursorPos; /**< Позиция первого курсора. */
    sf::Vector2f secondCursorPos; /**< Позиция второго курсора. */
    sf::Vector2f thirdCursorPos; /**< Позиция третьего курсора. */

    sf::Vector2f sideCursorRectangle1_1Pos; /**< Позиция прямоугольника 1_1 для создания вспомогательного курсора 1. */
    sf::Vector2f sideCursorRectangle1_2Pos; /**< Позиция прямоугольника 1_2 для создания вспомогательного курсора 1. */
    sf::Vector2f sideCursorRectangle1_3Pos; /**< Позиция прямоугольника 1_3 для создания вспомогательного курсора 2. */
    sf::Vector2f sideCursorRectangle1_4Pos; /**< Позиция прямоугольника 1_4 для создания вспомогательного курсора 2. */

    sf::Vector2f sideCursorRectangle2_1Pos; /**< Позиция прямоугольника 2_1 для создания вспомогательного курсора 3. */
    sf::Vector2f sideCursorRectangle2_2Pos; /**< Позиция прямоугольника 2_2 для создания вспомогательного курсора 3. */
    sf::Vector2f sideCursorRectangle2_3Pos; /**< Позиция прямоугольника 2_3 для создания вспомогательного курсора 4. */
    sf::Vector2f sideCursorRectangle2_4Pos; /**< Позиция прямоугольника 2_4 для создания вспомогательного курсора 4. */

    sf::Vector2f sideCursorRectangle3_1Pos; /**< Позиция прямоугольника 3_1 для создания вспомогательного курсора 5. */
    sf::Vector2f sideCursorRectangle3_2Pos; /**< Позиция прямоугольника 3_2 для создания вспомогательного курсора 5. */
    sf::Vector2f sideCursorRectangle3_3Pos; /**< Позиция прямоугольника 3_3 для создания вспомогательного курсора 6. */
    sf::Vector2f sideCursorRectangle3_4Pos; /**< Позиция прямоугольника 3_4 для создания вспомогательного курсора 6. */

    sf::BlendMode overlayBlendMode; /**< Режим наложения для изображений. */

    float firstZoom; /**< Уровень масштабирования для первого изображения. */
    float secondZoom; /**< Уровень масштабирования для второго изображения. */
    float thirdZoom; /**< Уровень масштабирования для третьего изображения. */

    int activeImage; /**< Индекс активного изображения. */


    /**
     * @brief Обновляет уровень масштабирования других изображений, соответствуя активному изображению.
     */
    void updateOtherImagesZoom() {
        float activeZoom = getActiveZoom();
        
        firstZoom = activeZoom;
        secondZoom = activeZoom;
        thirdZoom = activeZoom;
    }


    /**
     * @brief Ограничивает позицию курсора в пределах изображения.
     * @param cursorPos Позиция курсора, которую нужно ограничить.
     * @param image Изображение, для которого ограничивается позиция курсора.
     */
    void constrainCursorToBounds(sf::Vector2f& cursorPos, const Image& image) {
        // Проверка и коррекция границ курсора внутри спрайта
        if (cursorPos.x < 0) {
            cursorPos.x = 0;
        }
        else if (cursorPos.x > window.getSize().x) {
            cursorPos.x = static_cast<float>(window.getSize().x);
        }

        if (cursorPos.y < 0) {
            cursorPos.y = 0;
        }
        else if (cursorPos.y > window.getSize().y) {
            cursorPos.y = static_cast<float>(window.getSize().y);
        }
    }


    /**
     * @brief Накладывает первое изображение на второе и сохраняет результат в третьем изображении.
     * @param image1 Первое изображение.
     * @param image2 Второе изображение.
     * @param resultImage Результирующее изображение после наложения.
     */
    void overlayImage(const Image& image1, const Image& image2, Image& resultImage) {

        const sf::Texture& texture1 = image1.internalTexture.getTexture();
        const sf::Texture& texture2 = image2.internalTexture.getTexture();

        // Создание спрайтов для изображений
        sf::Sprite sprite1(texture1);
        sf::Sprite sprite2(texture2);

        // Получение размеров изображений
        sf::Vector2u imageSize1 = texture1.getSize();
        sf::Vector2u imageSize2 = texture2.getSize();

        // Определение размера результирующего изображения
        unsigned int resultWidth = std::max(imageSize1.x, imageSize2.x);
        unsigned int resultHeight = std::max(imageSize1.y, imageSize2.y);

        resultImage.internalTexture.create(resultWidth, resultHeight);

        resultImage.internalTexture.clear(sf::Color(0, 0, 0, 0));

        sf::RenderTexture renderTexture;
        renderTexture.create(resultWidth, resultHeight);

        renderTexture.clear(sf::Color::Transparent);
        renderTexture.draw(sprite1);

        sf::RenderStates states;
        states.blendMode = sf::BlendMultiply;  
        renderTexture.draw(sprite2, states);

        renderTexture.display();

        sf::Texture resultTexture = renderTexture.getTexture();
        resultImage.internalTexture.draw(sf::Sprite(resultTexture));
        
        resultImage.internalTexture.display();
    }


    /**
    * @brief Конструктор по умолчанию для структуры App.
    */
    App() : window(sf::VideoMode(1600, 800), "AstMarker"), firstZoom(1.0f), secondZoom(1.0f), thirdZoom(1.0f), activeImage(0) {

        firstIm.internalTexture.create(window.getSize().x / 3, window.getSize().y);
        secondIm.internalTexture.create(window.getSize().x / 3, window.getSize().y);
        thirdIm.internalTexture.create(window.getSize().x / 3, window.getSize().y);


        firstCursorPos = sf::Vector2f(window.getSize().x / 6, window.getSize().y / 2);
        secondCursorPos = sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2);
        thirdCursorPos = sf::Vector2f(window.getSize().x * 5 / 6, window.getSize().y / 2);


        overlayBlendMode = sf::BlendMode(sf::BlendMode::Factor::SrcAlpha, sf::BlendMode::Factor::OneMinusSrcAlpha, sf::BlendMode::Equation::Add,
            sf::BlendMode::Factor::One, sf::BlendMode::Factor::OneMinusSrcAlpha, sf::BlendMode::Equation::Add);
    }


    /**
    * @brief Обрабатывает события ввода пользователя.
    */
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

                if (mousePosition.x < window.getSize().x / 3.0) {
                    activeImage = 0;
                }
                else if (mousePosition.x < window.getSize().x / 3.0 * 2) {
                    activeImage = 1;
                }
                else {
                    activeImage = 2;
                }

                auto oldZoom = getActiveZoom();

                // Масштабирование колесиком мыши
                if (event.mouseWheelScroll.delta > 0) {
                    setActiveZoom(getActiveZoom() * 1.1f);
                }
                else {
                    setActiveZoom(getActiveZoom() / 1.1f);
                }

                // Определение точки отсчета для масштабирования
                sf::Vector2f anchorPoint;
                switch (activeImage) {
                case 0:
                    anchorPoint = firstCursorPos;
                    break;
                case 1:
                    anchorPoint = secondCursorPos;
                    break;
                case 2:
                    anchorPoint = thirdCursorPos;
                    break;
                }

                // Применение масштабирования с учетом позиции курсора
                getActiveImage().sprite.setScale(getActiveZoom(), getActiveZoom());
                translate = anchorPoint - (anchorPoint - translate) * (getActiveZoom() / oldZoom);
                

                updateOtherImagesZoom();

            }
            else if (event.type == sf::Event::MouseMoved) {
                // Движение мыши
                sf::Vector2f newCoord(event.mouseMove.x, event.mouseMove.y);

                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
                sf::Vector2f mousePosFloat4Second(mousePosFloat.x - static_cast<float>(window.getSize().x) / 3.0f, mousePosFloat.y);

                firstCursorPos = mousePosFloat;
                secondCursorPos = mousePosFloat - sf::Vector2f(window.getSize().x / 3.0f, 0);
                thirdCursorPos = mousePosFloat - sf::Vector2f(window.getSize().x / 3.0f * 2.0f, 0);


                sideCursorRectangle1_1Pos = sf::Vector2f(firstCursorPos.x - 6.6, firstCursorPos.y);
                sideCursorRectangle1_2Pos = sf::Vector2f(firstCursorPos.x, firstCursorPos.y - 6.6);

                sideCursorRectangle1_3Pos = sf::Vector2f(firstCursorPos.x - 6.6 - window.getSize().x / 3.0f, firstCursorPos.y);
                sideCursorRectangle1_4Pos = sf::Vector2f(firstCursorPos.x - window.getSize().x / 3.0f, firstCursorPos.y - 6.6);

                sideCursorRectangle2_1Pos = sf::Vector2f(secondCursorPos.x - 6.6, secondCursorPos.y);
                sideCursorRectangle2_2Pos = sf::Vector2f(secondCursorPos.x, secondCursorPos.y - 6.6);

                sideCursorRectangle2_3Pos = sf::Vector2f(secondCursorPos.x - 6.6 + window.getSize().x, secondCursorPos.y);
                sideCursorRectangle2_4Pos = sf::Vector2f(secondCursorPos.x + window.getSize().x, secondCursorPos.y - 6.6);

                sideCursorRectangle3_1Pos = sf::Vector2f(thirdCursorPos.x - 6.6, thirdCursorPos.y);
                sideCursorRectangle3_2Pos = sf::Vector2f(thirdCursorPos.x, thirdCursorPos.y - 6.6);

                sideCursorRectangle3_3Pos = sf::Vector2f(thirdCursorPos.x - 6.6 + window.getSize().x, thirdCursorPos.y);
                sideCursorRectangle3_4Pos = sf::Vector2f(thirdCursorPos.x + window.getSize().x, thirdCursorPos.y - 6.6);


                // Проверка и коррекция границ курсоров
                constrainCursorToBounds(firstCursorPos, firstIm);
                constrainCursorToBounds(secondCursorPos, secondIm);
                constrainCursorToBounds(thirdCursorPos, thirdIm);


                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    translate += newCoord - mouseCoord;
                }
                mouseCoord = newCoord;

            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePosFloat(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
               
            }            
        }
    }


    /**
    * @brief Получает уровень масштабирования активного изображения.
    * @return Уровень масштабирования активного изображения.
    */
    float getActiveZoom() {
        switch (activeImage) {
        case 0:
            return firstZoom;
        case 1:
            return secondZoom;
        case 2:
            return thirdZoom;
        default:
            return 1.0f;
        }
    }


    /**
     * @brief Устанавливает уровень масштабирования активного изображения.
     * @param zoom Уровень масштабирования для установки.
     */
    void setActiveZoom(float zoom) {
        switch (activeImage) {
        case 0:
            firstZoom = zoom;
            break;
        case 1:
            secondZoom = zoom;
            break;
        case 2:
            thirdZoom = zoom;
            break;
        default:
            break;
        }
    }


    /**
     * @brief Получает ссылку на активное изображение.
     * @return Ссылка на активное изображение.
     */
    Image& getActiveImage() {
        switch (activeImage) {
        case 0:
            return firstIm;
        case 1:
            return secondIm;
        case 2:
            return thirdIm;
        default:
            return firstIm; 
        }
    }


    /**
     * @brief Обновляет состояние приложения.
     */
    void update() {
        ImGui::SFML::Update(window, sf::seconds(1.0f / 60.0f));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

        if (ImGui::BeginMainMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                if (ImGui::MenuItem("Open Image 1")) firstIm.openImage();
                if (ImGui::MenuItem("Open Image 2")) secondIm.openImage();
                ImGui::Separator();
                if (ImGui::MenuItem("Import 1st Image points", nullptr, false, true));
                if (ImGui::MenuItem("Import 2nd Image points", nullptr, false, true));
                ImGui::Separator();
                if (ImGui::MenuItem("Export 1st Image points", nullptr, false, true));
                if (ImGui::MenuItem("Export 2nd Image points", nullptr, false, true));
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

            ImGui::Columns(4);
            ImGui::Text("win size: %d %d", window.getSize().x, window.getSize().y);
            ImGui::NextColumn();
            ImGui::Text("translate: %f %f", translate.x, translate.y);
            ImGui::NextColumn();
            ImGui::Text("zoom: %f", secondZoom);
            ImGui::NextColumn();
            ImGui::Text("mouse: %d %d", sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
            
        }
        ImGui::End();
        ImGui::PopStyleColor();

    }

    /**
     * @brief Отрисовывает приложение.
     */
    void render() {

        ImVec2 screenSize = ImGui::GetIO().DisplaySize;
                
        ImVec2 windowSize = ImVec2(screenSize.x / 3, screenSize.y - 19 - 30);
        ImVec2 windowPos1 = ImVec2(0, 19);
        ImVec2 windowPos2 = ImVec2(screenSize.x / 3, 19);
        ImVec2 windowPos3 = ImVec2(2 * screenSize.x / 3, 19);

        window.clear();

        ImGui::SetNextWindowPos(windowPos1);
        ImGui::SetNextWindowSize(windowSize);
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.9f, 0.9f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::Begin("FIRST WINDOW", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        if (firstIm.is_opened) {
            firstIm.internalTexture.clear();
            sf::Sprite internalSprite;
            internalSprite.setTexture(firstIm.internalTexture.getTexture());
            firstIm.sprite.setPosition(translate);
            firstIm.sprite.setScale(firstZoom, firstZoom);

            firstIm.internalTexture.draw(firstIm.sprite);
          
            firstIm.internalTexture.display();
            window.draw(internalSprite);
        }
        ImGui::End();


        ImGui::SetNextWindowPos(windowPos2);
        ImGui::SetNextWindowSize(windowSize);
        ImGui::Begin("SECOND WINDOW", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        if (secondIm.is_opened) {
            secondIm.internalTexture.clear();
            sf::Sprite internalSprite;
            internalSprite.setTexture(secondIm.internalTexture.getTexture());
            internalSprite.move(window.getSize().x / 3.0, 0);
            secondIm.sprite.setPosition(translate);
            secondIm.sprite.setScale(secondZoom, secondZoom);

            secondIm.internalTexture.draw(secondIm.sprite);
            
            secondIm.internalTexture.display();
            window.draw(internalSprite);            
        }
        ImGui::End();

        ImGui::SetNextWindowPos(windowPos3);
        ImGui::SetNextWindowSize(windowSize);
        ImGui::Begin("OVERLAY WINDOW", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
        if (firstIm.is_opened && secondIm.is_opened) {

            overlayImage(firstIm, secondIm, thirdIm);
            sf::Sprite internalSprite;
            internalSprite.setTexture(thirdIm.internalTexture.getTexture());
            internalSprite.move(window.getSize().x / 3.0 * 2, 0);
            thirdIm.sprite.setPosition(translate);
            thirdIm.sprite.setScale(thirdZoom, thirdZoom);
            thirdIm.internalTexture.draw(thirdIm.sprite);

            thirdIm.internalTexture.display();
            window.draw(internalSprite);


            sf::RectangleShape cursor1_1(sf::Vector2f(18, 5));
            cursor1_1.setFillColor(sf::Color::Green);
            cursor1_1.setPosition(sideCursorRectangle1_1Pos);
            if (activeImage != 0) {
                window.draw(cursor1_1);
            }

            sf::RectangleShape cursor1_2(sf::Vector2f(5, 18));
            cursor1_2.setFillColor(sf::Color::Green);
            cursor1_2.setPosition(sideCursorRectangle1_2Pos);
            if (activeImage != 0) {
                window.draw(cursor1_2);
            }

            sf::RectangleShape cursor1_3(sf::Vector2f(18, 5));
            cursor1_3.setFillColor(sf::Color::Green);
            cursor1_3.setPosition(sideCursorRectangle1_3Pos);
            if (activeImage != 0) {
                window.draw(cursor1_3);
            }

            sf::RectangleShape cursor1_4(sf::Vector2f(5, 18));
            cursor1_4.setFillColor(sf::Color::Green);
            cursor1_4.setPosition(sideCursorRectangle1_4Pos);
            if (activeImage != 0) {
                window.draw(cursor1_4);
            }



            sf::RectangleShape cursor2_1(sf::Vector2f(18, 5));
            cursor2_1.setFillColor(sf::Color::Green);
            cursor2_1.setPosition(sideCursorRectangle2_1Pos);
            constrainCursorToBounds(secondCursorPos, secondIm);
            if (activeImage != 1) {
                window.draw(cursor2_1);
            }

            sf::RectangleShape cursor2_2(sf::Vector2f(5, 18));
            cursor2_2.setFillColor(sf::Color::Green);
            cursor2_2.setPosition(sideCursorRectangle2_2Pos);
            constrainCursorToBounds(secondCursorPos, secondIm);
            if (activeImage != 1) {
                window.draw(cursor2_2);
            }

            sf::RectangleShape cursor2_3(sf::Vector2f(18, 5));
            cursor2_3.setFillColor(sf::Color::Green);
            cursor2_3.setPosition(sideCursorRectangle2_3Pos);
            constrainCursorToBounds(secondCursorPos, secondIm);
            if (activeImage != 1) {
                window.draw(cursor2_3);
            }

            sf::RectangleShape cursor2_4(sf::Vector2f(5, 18));
            cursor2_4.setFillColor(sf::Color::Green);
            cursor2_4.setPosition(sideCursorRectangle2_4Pos);
            constrainCursorToBounds(secondCursorPos, secondIm);
            if (activeImage != 1) {
                window.draw(cursor2_4);
            }
            


            sf::RectangleShape cursor3_1(sf::Vector2f(18, 5));
            cursor3_1.setFillColor(sf::Color::Green);
            cursor3_1.setPosition(sideCursorRectangle3_1Pos);
            constrainCursorToBounds(thirdCursorPos, thirdIm);
            if (activeImage != 2) {
                window.draw(cursor3_1);
            }

            sf::RectangleShape cursor3_2(sf::Vector2f(5, 18));
            cursor3_2.setFillColor(sf::Color::Green);
            cursor3_2.setPosition(sideCursorRectangle3_2Pos);
            constrainCursorToBounds(thirdCursorPos, thirdIm);
            if (activeImage != 2) {
                window.draw(cursor3_2);
            }

            sf::RectangleShape cursor3_3(sf::Vector2f(18, 5));
            cursor3_3.setFillColor(sf::Color::Green);
            cursor3_3.setPosition(sideCursorRectangle3_3Pos);
            constrainCursorToBounds(thirdCursorPos, thirdIm);
            if (activeImage != 2) {
                window.draw(cursor3_3);
            }

            sf::RectangleShape cursor3_4(sf::Vector2f(5, 18));
            cursor3_4.setFillColor(sf::Color::Green);
            cursor3_4.setPosition(sideCursorRectangle3_4Pos);
            constrainCursorToBounds(thirdCursorPos, thirdIm);
            if (activeImage != 2) {
                window.draw(cursor3_4);
            }          
        }
        ImGui::End();

        ImGui::PopStyleColor();
        ImGui::PopStyleColor();

        ImGui::SFML::Render(window);
        window.display();
    }

    /**
     * @brief Запускает цикл приложения.
     */
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

/**
 * @brief Главная функция, где создается объект App и запускается приложение.
 * @return Статус завершения программы.
 */
int main() {
    App app;
    app.run();

    return 0;
}
