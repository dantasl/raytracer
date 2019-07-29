/**
 * @file                DepthIntegrator.cpp
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file implements the Depth Color integrator
 * @version             0.1
 * @date                2019-05-29
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/integrators/DepthIntegrator.h"

using namespace raytracer;

Color DepthIntegrator::Li(const Ray &ray, const Scene &scene, Sampler &sampler,
                          real_value x, real_value y) const
{
    SurfaceInteration isect;
    if (scene.intersect(ray, &isect))
    {
       // We must calculate the linear interpolation
       float delta = (isect.ray_t - t_min) / (t_max - t_min); 
       real_value r = near_color.r() + (far_color.r() - near_color.r()) * delta;
       real_value g = near_color.g() + (far_color.g() - near_color.g()) * delta;
       real_value b = near_color.b() + (far_color.b() - near_color.b()) * delta;
       return Color(r, g, b);
    }
    else return far_color;
}

void DepthIntegrator::preprocess(const Scene &scene)
{
    // This will find the t_min and the t_max of the given scene
    SurfaceInteration isect;
    for ( int y = camera->get_film()->height - 1 ; y >= 0 ; y-- )
    {
        for( int x = 0 ; x < camera->get_film()->width ; x++ )
        {
            Ray r = camera->generate_ray(x, y);
            if (scene.intersect(r, &isect))
            {
                if (isect.ray_t < t_min) t_min = isect.ray_t;
                if (isect.ray_t > t_max) t_max = isect.ray_t;
            }
        }
    }
}