/**
 * @file            Spotlight.h
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This file defines the Spotlight light.
 * @version         0.1
 * @date            2019-06-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_SPOTLIGHT_H
#define RAYTRACER_SPOTLIGHT_H

#include "Light.h"

namespace raytracer
{
    class Spotlight: public Light
    {
        private:
            Point light_at;
            Point point_at;
            float fall_off;
            float cut_off;
        
        public:
            /**
             * @brief Construct a new Spotlight object
             * 
             * @param intensity 
             * @param ligth_at 
             * @param point_at 
             * @param fall_off 
             * @param cut_off 
             */
            Spotlight(Vector &intensity, Point &light_at, Point &point_at,
                      float fall_off, float cut_off)
                : Light{intensity}
                , light_at{light_at}
                , point_at{point_at}
                , fall_off{fall_off}
                , cut_off{cut_off}
                {/* empty */}
            
            /**
             * @brief Destroy the Spotlight object
             */
            ~Spotlight() = default;

            /**
             * @brief       Computes the Spotlight falloff
             * 
             * @param w 
             * @return float 
             */
            float falloff(const Vector &w) const;

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

#endif // RAYTRACER_SPOTLIGHT_H