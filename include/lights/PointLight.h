/**
 * @file                PointLight.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the Point Light.
 * @version             0.1
 * @date                2019-06-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_POINT_LIGHT_H
#define RAYTRACER_POINT_LIGHT_H

#include "Light.h"

namespace raytracer
{
    class PointLight: public Light
    {
        private:
            Point light_at;
        
        public:
            /**
             * 
             * @brief Construct a new Point Light object
             * 
             * @param intensity 
             * @param position 
             */
            PointLight(Vector &intensity, Point &position)
                : Light{intensity}
                , light_at{position}
                {/* empty */}

            /**
             * @brief Destroy the Point Light object
             */
            ~PointLight() = default;

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

#endif // RAYTRACER_POINT_LIGHT_H