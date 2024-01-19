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

};

#endif //ASTMARKER_IMAGE_H
