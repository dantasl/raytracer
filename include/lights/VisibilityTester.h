/**
 * @file                VisibilityTester.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the Visibility Tester
 * @version             0.1
 * @date                2019-06-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_VISIBILITYTESTER_H
#define RAYTRACER_VISIBILITYTESTER_H

#include "../SurfaceInteration.h"
#include "../Scene.h"
#include "../Ray.h"

namespace raytracer
{
    class Scene;
    
    class VisibilityTester
    {
        private:
            SurfaceInteration isect_one;
            SurfaceInteration isect_two;

            /**
             * @brief   This is a helper function to cast a ray
             * 
             * @return std::shared_ptr<Ray> 
             */
            std::shared_ptr<Ray> raycaster() const;

        public:
        
            /**
             * @brief Construct a new Visibility Tester object
             * 
             * @param s1 
             * @param s2 
             */
            VisibilityTester(const SurfaceInteration &s1, const SurfaceInteration &s2)
                : isect_one{s1}
                , isect_two{s2}
                {/* empty */}

            /**
             * @brief Construct a new Visibility Tester object
             */
            VisibilityTester() = default;

            /**
             * @brief Destroy the Visibility Tester object
             */
            ~VisibilityTester() = default;

            /**
             * @brief          Casts a shadow ray and check if it suffered
             *                 occlusion. 
             * 
             * @param scene     The scene containing the shapes
             * @return true     If occlusion happened
             * @return false    Otherwise
             */
            bool unoccluded(const Scene &scene);
    };
}

#endif // RAYTRACER_VISIBILITYTESTER_H