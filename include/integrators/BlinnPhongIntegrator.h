/**
 * @file                BlinnPhongIntegrator.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the Blinn Phong Integrator
 * @version             0.1
 * @date                2019-05-31
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_BLINN_PHONG_INTEGRATOR_H
#define RAYTRACER_BLINN_PHONG_INTEGRATOR_H

#include "SampleIntegrator.h"
#include "../shapes/Boundaries.h"
#include "../materials/BlinnPhongMaterial.h"

namespace raytracer
{
    class BlinnPhongIntegrator: public SampleIntegrator
    {
        public:
            Boundaries world_boundaries; // Boundaries of all elements of the world.

            /**
             * @brief Construct a new Blinn Phong Integrator object
             * 
             * @param cam 
             * @param sampler 
             */
            BlinnPhongIntegrator(std::shared_ptr<Camera> cam, std::shared_ptr<Sampler> sampler)
                : SampleIntegrator(sampler, cam)
                {/* empty */}

            /**
             * @brief Destroy the Blinn Phong Integrator object
             */
            ~BlinnPhongIntegrator() = default;

            /**
             * @brief           This method is a pure virtual method that returns the incident radiance
             *                  at the origin of a given ray.
             * 
             * @param ray       The ray to check the incident radiance
             * @param scene     The scene
             * @param sampler   The sampler
             * @return Color    The resulting color 
             */
            Color Li(const Ray &ray, const Scene &scene, Sampler &sampler, 
                     real_value x, real_value y) const;

            void preprocess(const Scene &scene)
            {
                world_boundaries = scene.scene_boundaries;
            }       
    };
}

#endif // RAYTRACER_BLINN_PHONG_INTEGRATOR_H