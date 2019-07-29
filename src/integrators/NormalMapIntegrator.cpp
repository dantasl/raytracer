/**
 * @file            NormalMapIntegrator.cpp
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This file implements the Normal Map Integrator
 * @version         0.1
 * @date            2019-05-25
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/integrators/NormalMapIntegrator.h"

using namespace raytracer;

Color raytracer::NormalMapIntegrator::Li(const Ray &ray, const Scene &scene,
                                         Sampler &sampler, real_value x,
                                         real_value y) const
{
    SurfaceInteration isect;
    if (scene.intersect(ray, &isect))
    {
        Vector normal = isect.n;
        real_value r = ((normal.x() + 1.0f) / 2.0f) * 255.0f;
        real_value g = ((normal.y() + 1.0f) / 2.0f) * 255.0f;
        real_value b = ((normal.z() + 1.0f) / 2.0f) * 255.0f;
        return Color(r, g, b);                        
    }
    else
    {
        return scene.background->sample(float(x)/float(camera->get_film()->width),
                                        float(y)/float(camera->get_film()->height));
    }    
}