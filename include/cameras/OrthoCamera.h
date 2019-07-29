/**
 * @file        OrthoCamera.h
 * @author      Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief       This file definines an Ortographic Camera.
 * @version     0.1
 * @date        2019-04-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_ORTHOCAMERA_H
#define RAYTRACER_ORTHOCAMERA_H

#include "Camera.h"
#include <iostream>

namespace raytracer
{
    class OrthoCamera: public Camera
    {
        private:
            real_value left, right, bottom, top; //<! Plane view plane dimensions

        public:
            /**
             * @brief Construct a new Ortho Camera object
             * 
             * @param width         The width of the camera
             * @param height        The height of the camera
             * @param look_from     The origin ot the camera
             * @param look_at       The target of the camera
             * @param vup           The camera's up vector
             * @param left          The camera's left corner
             * @param right         The camera's right corner
             * @param bottom        The camera's bottom corner
             * @param top           The camera's top corner 
             */
            OrthoCamera(int width, int height, Point look_from, Point look_at, Vector vup,
                        std::shared_ptr<Film> film, real_value left, real_value right,
                        real_value bottom, real_value top)
                : Camera(width, height, look_from, look_at, vup, film)
                , left(left)
                , right(right)
                , bottom(bottom)
                , top(top)
                {/* empty */}

            /**
             * @brief Destroy the Ortho Camera object
             */
            ~OrthoCamera() = default;

            /**
             * @brief           Generates a ray that passes throught the given coordinates.
             * 
             * @param x         X coordinate of the point to generate a ray.
             * @param y         Y coordinate of the point to generate a ray.
             * @return Ray      The generated Ray.
             */
            Ray generate_ray(real_value x, real_value y);
    };
}

#endif //RAYTRACER_ORTHOCAMERA_H
