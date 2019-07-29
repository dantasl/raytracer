/**
 * @file        OrthoCamera.cpp
 * @author      Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief       This file implements the OrthoCamera class.
 * @version     0.1
 * @date        2019-04-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/cameras/OrthoCamera.h"
#include "../Vec3.cpp"

using namespace raytracer;

Ray OrthoCamera::generate_ray(real_value x, real_value y)
{
    // Part one: mapping pixels to screen space
    real_value u = left + (right - left) * (x + 0.5)/width;
    real_value v = bottom + (top - bottom) * (y + 0.5)/height;      

    // Part two: determining the camera frame
    Vector gaze = look_at - look_from;
    Vector wV = -gaze;
    wV.make_unit_vector();
    Vector uV = cross(vUp, wV);
    uV.make_unit_vector();
    Vector vV = cross(wV, uV);
    vV.make_unit_vector();
    Point e = look_from;

    // Part three: generating the rays
    Point origin = e + (u * uV) + (v * vV);
    Vector direction = -wV;

    return Ray(origin, direction);
}