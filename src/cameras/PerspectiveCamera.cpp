/**
 * @file            PerspectiveCamera.cpp
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This file implements the PerspectiveCamera class.
 * @version         0.1
 * @date            2019-04-08
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/cameras/PerspectiveCamera.h"
#include "../Vec3.cpp"

using namespace raytracer;

Ray PerspectiveCamera::generate_ray(real_value x, real_value y)
{
    // Find the half-height and half-width
    auto hh = tan( (fovy * 0.01745329252)  /2) * fdistance;
    auto hw = aspect * hh;
    
    real_value left, right, top, bottom;
    left = -hw;
    right = hw;
    top = hh;
    bottom = -hh;     

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
    Point origin = e;
    Vector direction = -(fdistance) * wV + u * uV + v * vV;

    return Ray(origin, direction);
}