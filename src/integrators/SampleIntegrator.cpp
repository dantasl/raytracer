/**
 * @file                SampleIntegrator.cpp
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file implements the Sample Integrator
 * @version             0.1
 * @date                2019-05-20
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/integrators/SampleIntegrator.h"

using namespace raytracer;

SampleIntegrator::SampleIntegrator(std::shared_ptr<Sampler> sampler, std::shared_ptr<Camera> cam)
    : sampler{sampler}
    , camera{cam}
    {/* empty */}

void SampleIntegrator::render(const Scene &scene)
{
    preprocess(scene);
    for ( int y = camera->get_film()->height - 1 ; y >= 0 ; y-- )
    {
        for( int x = 0 ; x < camera->get_film()->width ; x++ )
        {
            Ray r = camera->generate_ray(x, y);
            Color c = Li( r, scene, *sampler, x, y );
            Point p(x, y, 0);
            camera->get_film()->paint_pixel(p, c);
        }
    }
}