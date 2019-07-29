/**
 * @file                AmbientLight.cpp
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file implements the Ambient Light.
 * @version             0.1
 * @date                2019-06-04
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/lights/AmbientLight.h"

using namespace raytracer;

Vector AmbientLight::Li(const SurfaceInteration &isect, Vector *wi,
                        VisibilityTester *vt) const
{
    return intensity;
}