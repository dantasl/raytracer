/**
 * @file                FlatIntegrator.cpp
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file implements the Flat Integrator
 * @version             0.1
 * @date                2019-05-17
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/integrators/FlatIntegrator.h"

using namespace raytracer;

Color raytracer::FlatIntegrator::Li(const Ray &ray, const Scene &scene,
                                    Sampler &sampler, real_value x,
                                    real_value y) const
{ 
    SurfaceInteration isect;
    if (scene.intersect(ray, &isect))
    {
        const FlatMaterial *fm = dynamic_cast<const FlatMaterial*>( isect.primitive->get_material() );
        return fm->kd();       
    }
    else
    {
        return scene.background->sample(float(x)/float(camera->get_film()->width),
                                        float(y)/float(camera->get_film()->height));
    }
}