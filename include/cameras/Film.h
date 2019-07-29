/**
 * @file            Film.h
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This file defines a Film
 * @version         0.1
 * @date            2019-05-15
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_FILM_H
#define RAYTRACER_FILM_H

#include "../Vec3.h"
#include <fstream>
#include <string>
#include <iostream>
#include <memory>

namespace raytracer
{
    typedef unsigned char component_t;

    enum ENV { PIXEL_CHANNELS = 3 };

    class Film
    {
        public:
            std::size_t width, height;
            std::string filename;
            std::unique_ptr<component_t[]> pixels;
            
            /**
             * @brief Construct a new Film object
             */
            Film() = default;

            /**
             * @brief Construct a new Film object
             * 
             * @param width
             * @param height 
             * @param filename 
             */
            Film(std::size_t width, std::size_t height, std::string filename)
                : width(width)
                , height(height)
                , filename(filename)
                , pixels{new component_t[width * height * ENV::PIXEL_CHANNELS]}
                {/* empty here, space cowboy */}

            /**
             * @brief Destroy the Film object
             */
            ~Film() = default;

            /**
             * @brief Get the pixels stored in the Film
             * 
             * @return component_t*     Pixels
             */
            component_t *get_image() const { return pixels.get(); }

            /**
             * @brief   Given a Point and a Color, "paints" that point with the color.
             * 
             * @param point     Point that coordinates a pixel to be painted
             * @param color     Color to be assigned to the pixel
             */
            void paint_pixel(const Point &point, const Color &color);

            /**
             * @brief   Saves the content of this Film into an image file.
             */
            void write_image();
    };
}

#endif // RAYTRACER_FILM_H