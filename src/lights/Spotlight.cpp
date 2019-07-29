/**
 * @file            Spotlight.cpp
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This file implements the Spotlight light.
 * @version         0.1
 * @date            2019-06-07
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/lights/Spotlight.h"
#include "../Vec3.cpp"
#include <cmath>

using namespace raytracer;

float Spotlight::falloff(const Vector &wi) const
{
    Vector w = wi;
    Vector l = point_at - light_at;
    float cos_theta = dot(l, -wi) / (norm(l) * norm(-wi));

    float cos_cut_off = std::cos(cut_off * 0.01745329252);
    float cos_fall_off = std::cos(fall_off * 0.01745329252);

    if (cos_theta < cos_cut_off) return 0;
    if (cos_theta > cos_fall_off) return 1;

    // Compute falloff inside cone
    float delta = (cos_theta - cos_cut_off) / (cos_fall_off - cos_cut_off);
    return (delta * delta) * (delta * delta);
}

Vector Spotlight::Li(const SurfaceInteration &isect,
                     Vector *wi, VisibilityTester *vt) const
{ 
    *wi = unit_vector(light_at - isect.p);
    *vt = VisibilityTester{isect, SurfaceInteration{light_at}};
    return intensity * falloff(*wi);
}