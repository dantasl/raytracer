/**
 * @file        Camera.h
 * @author      Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief       This file defines the abstraction of a Camera.
 * @version     0.1
 * @date        2019-04-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_CAMERA_H
#define RAYTRACER_CAMERA_H

#include "../Ray.h"
#include "../Vec3.h"
#include "Film.h"
#include <cmath>

namespace raytracer
{
    class Camera
    {
        protected:
            int width;                      //!< Width of the eye camera
            int height;                     //!< Height of the eye camera
            Point look_from;                //<! Where the camera is located
            Point look_at;                  //<! Wher e the camera is looking
            Vector vUp;                     //<! Up vector of the camera
            std::shared_ptr<Film> film;     //<! Reference to the Film

        public:
            /**
             * @brief Construct a new Camera object
             * 
             * @param width         Width of the camera
             * @param height        Height of the camera
             * @param look_from     The origin point of the camera
             * @param look_at       The target point of the camera
             * @param vup           The camera's vector up
             */
            Camera(int width, int height, Point look_from, Point look_at,
                   Vector vup, std::shared_ptr<Film> film)
                : width(width)
                , height(height)
                , look_from(look_from)
                , look_at(look_at)
                , vUp(vup)
                , film(film)
            {/* empty */}

            /**
             * @brief           Generates a ray that passes throught the given coordinates.
             * 
             * @param x         X coordinate of the point to generate a ray.
             * @param y         Y coordinate of the point to generate a ray.
             * @return Ray      The generated Ray.
             */
            virtual Ray generate_ray(real_value x, real_value y) = 0;
            
            /**
             * @brief Destroy the Camera object
             */
            virtual ~Camera() {}
            
            /**
             * @brief           Get the width of the camera
             * 
             * @return int      Width
             */
            inline int get_width(){ return width; }

            /**
             * @brief           Get the height of the camera
             * 
             * @return int      Height
             */
            inline int get_height(){ return height; }

            /**
             * @brief           Get the position of the camera
             * 
             * @return Point    Position of the camera
             */
            inline Point get_look_from(){ return look_from; }

            /**
             * @brief           Get the target of the camera
             * 
             * @return Point    Target of the camera
             */
            inline Point get_look_at(){ return look_at; }

            /**
             * @brief           Get the vector up of the camera
             * 
             * @return Vector     Vector up of the camera
             */
            inline Vector get_vup(){ return vUp; }

            inline std::shared_ptr<Film> get_film(){ return film; }
    };
}

#endif // RAYTRACER_CAMERA_H
