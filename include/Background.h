/**
 * @file            Background.h
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This file defines the Background class.
 * @version         0.1
 * @date            2019-03-29
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_BACKGROUND_H
#define RAYTRACER_BACKGROUND_H

#include "Vec3.h"

namespace raytracer
{
    class Background
    {
        public:
            /**
             * @brief The corners of the background retangle (i.e. its vertices).
             */
            Color corners[4];

            /**
             * @brief Construct a new Background object
             */
            Background() = default;
            
            /**
             * @brief Construct a new Background object given its four points.
             * 
             * @param bottom_left       Color of the bottom left part of the background.
             * @param top_left          Color of the top left part of the background.
             * @param top_right         Color of the top right part of the background.
             * @param bottom_right      Color of the bottom right part of the background.
             */
            Background(Color &bottom_left, Color &top_left, Color &top_right, Color &bottom_right);

            /**
             * @brief Destroy the Background object
             */
            ~Background() = default;

            /**
             * @brief Calculates a color on the background using bilinear interpolation.
             * 
             * @param point     Point to calculate color.
             * @return Color    Resulting color.
             */
            Color sample(real_value x, real_value y);
    };
}

#endif //RAYTRACER_BACKGROUND_H
