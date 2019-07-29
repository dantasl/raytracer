/**
 * @file            DirectionalLight.cpp
 * @autho           Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This file implements the Directional Light         
 * @version         0.1
 * @date            2019-06-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/lights/DirectionalLight.h"
#include "../Vec3.cpp"

using namespace raytracer;

Vector DirectionalLight::Li(const SurfaceInteration &isect,
                            Vector *wi, VisibilityTester *vt) const
{
    *wi = unit_vector(direction);
    Vector p = isect.p + (*wi) * world_bounds.diagonal();
    *vt = VisibilityTester(isect, SurfaceInteration{p});
    return intensity;
}