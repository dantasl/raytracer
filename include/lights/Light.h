/**
 * @file                Light.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines a Light 
 * @version             0.1
 * @date                2019-05-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_LIGHT_H
#define RAYTRACER_LIGHT_H

#include "../SurfaceInteration.h"
#include "../lights/VisibilityTester.h"
#include "../shapes/Boundaries.h"

namespace raytracer
{
    class SurfaceInteration;
    class VisibilityTester;
    
    class Light
    {
        protected:
            Vector intensity;
            Boundaries world_bounds;
        
        public:

            /**
             * @brief Construct a new Light object
             * 
             * @param intensity 
             */
            Light(const Vector &intensity)
                : intensity{intensity}
                {/* empty */}

            /**
             * @brief Construct a new Light object with light intensity default
             */
            Light(): intensity{ Vector(0.1, 0.1, 0.1) } {/* empty */}

            /**
             * @brief Destroy the Light object
             */
            virtual ~Light() = default;

            /**
             * @brief           Informs if this kind of light is ambient.
             * 
             * @return true     If light is ambient.
             * @return false    Otherwise.
             */
            virtual bool is_ambient() { return false; }

            /**
             * @brief           Get the intensity object
             * 
             * @return          The Vec3 of intensity value 
             */
            Vector get_intensity() { return intensity; }

            /**
             * @brief Set the world bounds object
             * 
             * @param bounds 
             */
            inline void set_world_bounds(const Boundaries &bounds)
            { 
                world_bounds = bounds;
            }

            /**
             * @brief           Pure virtual function to inform the contribution
             *                  of light on a point.
             * 
             * @param isect     The surface interaction
             * @param wi        The vector going in the lights direction
             * @param vt        The visibility tester
             * @return Vector   The light contribution
             */
            virtual Vector Li(const SurfaceInteration &isect, Vector *wi,
                              VisibilityTester *vt) const = 0;
    };
}

#endif // RAYTRACER_LIGHT_H