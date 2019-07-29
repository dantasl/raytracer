/**
 * @file                DirectionalLight.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the Directional Light
 * @version             0.1
 * @date                2019-06-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_DIRECTIONAL_LIGHT_H
#define RAYTRACER_DIRECTIONAL_LIGHT_H

#include "Light.h"

namespace raytracer
{
    class DirectionalLight: public Light
    {
        private:
            Vector direction;

        public:
            /**
             * @brief Construct a new Directional Light object
             * 
             * @param intensity 
             * @param direction 
             */
            DirectionalLight(Vector intensity, Vector direction)
                : Light{intensity}
                , direction{direction}
                {/* empty */}
            
            /**
             * @brief Destroy the Directional Light object
             */
            ~DirectionalLight() = default;

            /**
             * @brief   Gets the light's direction
             * 
             * @return Vector 
             */
            Vector light_direction() { return direction; }

             /**
             * @brief           Pure virtual function to inform the contribution
             *                  of light on a point.
             * 
             * @param isect     The surface interaction
             * @param wi        The vector going in the lights direction
             * @param vt        The visibility tester
             * @return Vector   The light contribution
             */
            Vector Li(const SurfaceInteration &isect,
                      Vector *wi, VisibilityTester *vt) const;
    };
}

#endif // RAYTRACER_DIRECTIONAL_LIGHT_H