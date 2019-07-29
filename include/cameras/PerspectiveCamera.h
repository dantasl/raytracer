/**
 * @file        PerspectiveCamera.h
 * @author      Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief       This file defines a Perspective Camera.
 * @version     0.1
 * @date        2019-04-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef PERSPECTIVE_CAMERA_H
#define PERSPECTIVE_CAMERA_H

#include "Camera.h"

namespace raytracer
{
    class PerspectiveCamera: public Camera
    {
        private:
            real_value fovy; //<! The vertical field of view
            real_value aspect; //<! Optional parameter, aspect ratio W/H
            real_value fdistance; //<! The focal distance

        public:
            /**
             * @brief Construct a new Perspective Camera object
             * 
             * @param width         The width of the camera
             * @param height        The height of the camera
             * @param look_from     The origin ot the camera
             * @param look_at       The target of the camera
             * @param vup           The camera's up vector
             * @param fovy          The verticial field of view
             * @param aspect        Aspect ratio
             * @param fdistance     The focal distance
             */
            PerspectiveCamera(int width, int height, Point look_from, Point look_at, Vector vup,
                              std::shared_ptr<Film> film, real_value fovy, real_value aspect,
                              real_value fdistance)
                : Camera(width, height, look_from, look_at, vup, film)
                , fovy(fovy)
                , aspect(aspect)
                , fdistance(fdistance)
                {/* empty */}

            /**
             * @brief Destroy the Perspective Camera object
             */
            ~PerspectiveCamera() = default;

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

#endif // PERSPECTIVE_CAMERA_H