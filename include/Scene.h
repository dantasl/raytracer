/**
 * @file                Scene.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines a Scene 
 * @version             0.1
 * @date                2019-05-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_SCENE_H
#define RAYTRACER_SCENE_H

#include "lights/Light.h"
#include "primitives/Primitive.h"
#include "Background.h"
#include <memory>
#include <vector>

namespace raytracer
{
    class Light;
    class Scene
    {
        private:
            std::shared_ptr<Primitive> aggregate; // The scene graph of objects, acceleration structure.
        
        public:
            std::vector<std::shared_ptr<Light>> lights; // list of lights
            std::shared_ptr<Background> background; // The background object.
            Boundaries scene_boundaries; // The boundaries of all elements of the scene.

            /**
             * @brief           Construct a new Scene object
             * 
             * @param ag        The primitive aggregate 
             * @param ls        The lights of the scene
             */
            Scene(std::shared_ptr<Primitive> ag, const std::vector<std::shared_ptr<Light>> &ls,
                  std::shared_ptr<Background> bkg)
                : aggregate{ag}
                , lights{ls}
                , background{bkg}
                {
                    // We can create the boundaries of the whole scene by calling the aggregate boundaries
                    scene_boundaries = aggregate->boundaries();
                }
            
            /**
             * @brief           Determines the intersection information
             * 
             * @param r         The ray
             * @param isect     The surface interation
             * @return true     If there is an intersection
             * @return false    If there is not
             */
            bool intersect(const Ray &r, SurfaceInteration *isect) const
            {
                return aggregate->intersect(r, isect);
            }

            /**
             * @brief           A faster version that only determines whether there is
             *                  an intersection or not. It doesn't calculate the info.
             *             
             * @param r         The ray
             * @return true     If there is an intersection
             * @return false    If there is not
             */
            bool intersect_p(const Ray &r) const
            {
                return aggregate->intersect_p(r);
            }
    };
}

#endif // RAYTRACER_SCENE_H