/**
 * @file                DepthIntegrator.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the Depth Integrator 
 * @version             0.1
 * @date                2019-05-29
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_DEPTHINTEGRATOR_H
#define RAYTRACER_DEPTHINTEGRATOR_H

#include "SampleIntegrator.h"
#include <limits>

namespace raytracer
{
    class DepthIntegrator: public SampleIntegrator
    {
        protected:
            Color near_color;
            Color far_color;
            float t_max = std::numeric_limits<float>::min();
            float t_min = std::numeric_limits<float>::max();

        public:
            
            /**
             * @brief               Construct a new Depth Integrator object
             * 
             * @param cam           The camera object 
             * @param sampler       The sampler object
             * @param near          The near color
             * @param far           The far color
             */
            DepthIntegrator(std::shared_ptr<Camera> cam, std::shared_ptr<Sampler> sampler,
                            Color near, Color far)
                : SampleIntegrator(sampler, cam)
                , near_color(near)
                , far_color(far)
                {/* empty */}
            
            /**
             * @brief Destroy the Depth Integrator object
             */
            ~DepthIntegrator() = default;

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
            
           /**
             * @brief           This type of integrator needs to preprocess the zmin and zmax.
             * 
             * @param scene     The scene.
             */
            void preprocess(const Scene &scene);

    };
}

#endif // RAYTRACER_DEPTHINTEGRATOR_H