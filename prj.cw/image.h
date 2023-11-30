#ifndef IMAGE_H
#define IMAGE_H



#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <glad/glad.h>

#include <cmath>
#include <algorithm>

/**
 * @brief Класс Image представляет изображение, состоящее из слоев.
 */
class Image {
public:
    /**
     * @brief Конструктор класса Image
     */
    Image();

    /**
     * @brief Деструктор класса Image
     */
//    virtual ~Image();

    std::string name; /**< Имя изображения */
    std::string fullPath; /**< Полный путь к изображению */
    bool isOpened;
    int size[2] = {256, 256}; /**< Размер изображения */
    GLuint _glindex; /**< Идентификатор текстуры OpenGL */
//    unsigned char *_data = nullptr; /**< Данные изображения */
    cv::Mat _data;
    void fromFile(const char *filename);
    void setScale(float scale);

    // Метод для наложения изображений с настройками полупрозрачности
    void overlay(const Image& img1, const Image& img2, double alpha) {
        cv::addWeighted(img1._data, alpha, img2._data, 1.0 - alpha, 0.0, _data);
        // Преобразование в формат с четырьмя каналами для правильной обработки альфа-канала
        cv::cvtColor(_data, _data, cv::COLOR_BGR2BGRA);
    }

    // Функция для обновления OpenGL-текстуры
    void updateGLTexture() {
        glBindTexture(GL_TEXTURE_2D, _glindex);

        // Устанавливаем параметры текстуры (может потребоваться настройка в зависимости от ваших требований)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Обновляем данные в текстуре
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _data.cols, _data.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data.ptr());

        glBindTexture(GL_TEXTURE_2D, 0);
    }
};

#endif // IMAGE_H
