/**
 * @file                PointLight.cpp
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file implements the Point Light.
 * @version             0.1
 * @date                2019-06-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/lights/PointLight.h"
#include "../Vec3.cpp"

using namespace raytracer;

Vector PointLight::Li(const SurfaceInteration &isect,
                      Vector *wi, VisibilityTester *vt) const
{
    *wi = unit_vector(light_at - isect.p);
    *vt = VisibilityTester(isect, SurfaceInteration{light_at});
    return intensity;
}