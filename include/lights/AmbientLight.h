/**
 * @file                AmbientLight.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the ambient light
 * @version             0.1
 * @date                2019-06-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_AMBIENT_LIGHT_H
#define RAYTRACER_AMBIENT_LIGHT_H

#include "Light.h"

namespace raytracer
{
    class AmbientLight: public Light
    {
        public:
            /**
             * @brief Construct a new Ambient Light object
             * 
             * @param intensity 
             */
            AmbientLight(const Vector &intensity)
                : Light(intensity)
                {/* empty */}

            /**
             * @brief Construct a new Ambient Light object with default ambient light
             */
            AmbientLight() : Light( Vector(0.1, 0.1, 0.1) ) {/* empty */}

            /**
             * @brief Destroy the Ambient Light object
             */
            ~AmbientLight() = default;

            /**
             * @brief           Informs if this kind of light is ambient.
             * 
             * @return true     If light is ambient.
             * @return false    Otherwise.
             */            
            bool is_ambient() { return true; }

            /**
             * @brief           Pure virtual function to inform the contribution
             *                  of light on a point.
             * 
             * @param isect     The surface interaction
             * @param wi        The vector going in the lights direction
             * @param vt        The visibility tester
             * @return Vector   The light contribution
             */
            Vector Li(const SurfaceInteration &isect, Vector *wi,
                      VisibilityTester *vt) const;
    };
}

#endif // RAYTRACER_AMBIENT_LIGHT_H