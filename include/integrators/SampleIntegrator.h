/**
 * @file                SampleIntegrator.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines a Sample Integrator
 * @version             0.1
 * @date                2019-05-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_SAMPLEINTEGRATOR_H
#define RAYTRACER_SAMPLEINTEGRATOR_H

#include <memory>
#include "Integrator.h"
#include "../Sampler.h"
#include "../cameras/Camera.h"
#include "../SurfaceInteration.h"
#include "../materials/FlatMaterial.h"

namespace raytracer
{
    class SampleIntegrator: public Integrator
    {
        private:
            std::shared_ptr<Sampler> sampler;
        
        protected:
            std::shared_ptr<Camera> camera;

        public:

            /**
             * @brief               Construct a new Sample Integrator object
             * 
             * @param cam           The camera object
             * @param sampler       The sampler object
             */
            SampleIntegrator(std::shared_ptr<Sampler> sampler, std::shared_ptr<Camera> cam);

            /**
             * @brief            This method is a pure virtual method that returns the incident radiance
             *                   at the origin of a given ray.
             * 
             * @param ray       The ray to check the incident radiance
             * @param scene     The scene
             * @param sampler   The sampler
             * @return Color    The resulting color
             */
            virtual Color Li(const Ray &ray, const Scene &scene, Sampler &sampler,
                             real_value x, real_value y) const = 0;

            /**
             * @brief           This method runs the main application loop that invokes the Li method
             *                  for each possible ray. 
             * 
             * @param scene     The scene
             */
            virtual void render(const Scene &scene);

            /**
             * @brief           This method is an optional method that might prepare a scene or any
             *                  auxiliary data structure for future processing.
             * 
             * @param scene     The scene
             */
            virtual void preprocess(const Scene &scene){}
    };
}

#endif // RAYTRACER_SAMPLEINTEGRATOR_H