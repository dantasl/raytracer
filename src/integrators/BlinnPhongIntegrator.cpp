/**
 * @file        BlinnPhongIntegrator.cpp
 * @author      Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief       This file implements the Blinn Phong Integrator.
 * @version     0.1
 * @date        2019-06-07
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/integrators/BlinnPhongIntegrator.h"
#include "../Vec3.cpp"

using namespace raytracer;

Color BlinnPhongIntegrator::Li(const Ray &ray, const Scene &scene,
                               Sampler &sampler, real_value x,
                               real_value y) const
{
    SurfaceInteration isect;
    if (scene.intersect(ray, &isect))
    {
        Point ambient_intensity = Point(0.0, 0.0, 0.0);
        Color L(0, 0, 0);
        Vector wi;
        VisibilityTester vt;

        // Getting information regarding the material
        /*const BlinnPhongMaterial *bpm = dynamic_cast<const BlinnPhongMaterial*>( isect.mat );
        Point _ka = bpm->ka();
        Point _kd = bpm->kd();
        Point _ks = bpm->ks();
        real_value ge = bpm->glossiness();*/

        Point _ka = Point(0.1, 0.1, 0.1);
        Point _kd = Point(0.1, 0.9, 0.9);
        Point _ks = Point(0.8, 0.8, 0.1);
        real_value ge = 128;

        // Now we must iterate over the lights to calculate their contribution
        for (auto l : scene.lights)
        {
            l->set_world_bounds(world_boundaries);

            if (l->is_ambient())
            {
                // Since the light is ambient, we simply calculate the intensity
                ambient_intensity = _ka * l->get_intensity();
            }
            else
            {
                // Light is not ambient, so we use Blinn-Phong model
                Vector intensity = l->Li(isect, &wi, &vt);
                
                Vector normal = isect.n;
                Vector wo = isect.wo;
                Vector h = wo + wi;
                h.make_unit_vector();

                if (vt.unoccluded(scene))
                {
                    L += _kd * intensity * fmax(0.0, dot(normal, wi));
                    L += _ks * intensity * pow(fmax(0.0, dot(normal, h)), ge);
                }
            }            
        }
        
        // Adding ambient light contribution and converting back to RGB
        L = (ambient_intensity + L) * 255;
        Color c{
            fmin(255.0, L.r()), fmin(255.0, L.g()), fmin(255.0, L.b())
        };        
        return c;
    }
    else
    {
        // We must simply sample the background
        return scene.background->sample(float(x)/float(camera->get_film()->width),
                                        float(y)/float(camera->get_film()->height));
    }    
}