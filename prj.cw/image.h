#include <SFML/Graphics.hpp>

#ifndef ASTMARKER_IMAGE_H
#define ASTMARKER_IMAGE_H

/**
 * @brief Класс для работы с изображением.
 */
class Image {
public:
    /**
     * @brief Конструктор по умолчанию.
     */
    Image();

    /**
     * @brief Деструктор по умолчанию.
     */
    ~Image();

    sf::Texture texture; /**< Текстура изображения. */
    sf::Sprite sprite;   /**< Спрайт изображения. */
    sf::RenderTexture internalTexture; /**< Внутренняя текстура. */

    bool is_opened = false; /**< Флаг, указывающий, открыто ли изображение. */

    /**
     * @brief Открывает изображение.
     */
    void openImage();


    sf::RectangleShape cursor1_1;  /**< Прямоугольник 1_1 для создания 1-го курсора. */
    sf::RectangleShape cursor1_2;  /**< Прямоугольник 1_2 для создания 1-го курсора. */
    sf::RectangleShape cursor1_3;  /**< Прямоугольник 1_3 для создания 2-го курсора. */
    sf::RectangleShape cursor1_4;  /**< Прямоугольник 1_4 для создания 2-го курсора. */
    sf::RectangleShape cursor2_1;  /**< Прямоугольник 2_1 для создания 3-го курсора. */
    sf::RectangleShape cursor2_2;  /**< Прямоугольник 2_2 для создания 3-го курсора. */
    sf::RectangleShape cursor2_3;  /**< Прямоугольник 2_3 для создания 4-го курсора. */
    sf::RectangleShape cursor2_4;  /**< Прямоугольник 2_4 для создания 4-го курсора. */
    sf::RectangleShape cursor3_1;  /**< Прямоугольник 3_1 для создания 5-го курсора. */
    sf::RectangleShape cursor3_2;  /**< Прямоугольник 3_2 для создания 5-го курсора. */
    sf::RectangleShape cursor3_3;  /**< Прямоугольник 3_3 для создания 6-го курсора. */
    sf::RectangleShape cursor3_4;  /**< Прямоугольник 3_4 для создания 6-го курсора. */
};

#endif //ASTMARKER_IMAGE_H
