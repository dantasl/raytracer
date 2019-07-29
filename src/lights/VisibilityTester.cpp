/**
 * @file                VisibilityTester.cpp
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file implements the Visibility Tester
 * @version             0.1
 * @date                2019-06-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/lights/VisibilityTester.h"
#include "../Vec3.cpp"

using namespace raytracer;

std::shared_ptr<Ray> VisibilityTester::raycaster() const
{
    Vector from_to = isect_two.p - isect_one.p;
    std::shared_ptr<Ray> ray(new Ray(isect_one.p, from_to));
    ray->t_max = 1;
    return ray;
}

bool VisibilityTester::unoccluded(const Scene &scene)
{
    auto ray = raycaster();
    return !scene.intersect(*ray, &isect_two);
}