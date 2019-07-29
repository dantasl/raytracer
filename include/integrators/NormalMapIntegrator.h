/**
 * @file                NormalMapIntegrator.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the Normal Map Integrator 
 * @version             0.1
 * @date                2019-05-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_NORMALMAPINTEGRATOR_H
#define RAYTRACER_NORMALMAPINTEGRATOR_H

#include "SampleIntegrator.h"

namespace raytracer
{
    class NormalMapIntegrator: public SampleIntegrator
    {
        public:
        /**
             * @brief           Construct a new Normal Map Integrator object
             * 
             * @param cam       The camera
             * @param sampler   The sampler
             */
            NormalMapIntegrator(std::shared_ptr<Camera> cam, std::shared_ptr<Sampler> sampler)
                : SampleIntegrator(sampler, cam)
                {/* empty */}

            /**
             * @brief Destroy the Normal Map Integrator object
             */
            ~NormalMapIntegrator(){}

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
             * @brief           This type of integrator does not need to preprocess anything.
             * 
             * @param scene     The scene.
             */
            void preprocess(const Scene &scene) {/* empty */}
    };
}

#endif // RAYTRACER_NORMALMAPINTEGRATOR_H