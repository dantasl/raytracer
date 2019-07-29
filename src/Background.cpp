/**
 * @file            Background.cpp
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This file implements the Background class.
 * @version         0.1
 * @date            2019-03-29
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../include/Background.h"
#include "Vec3.cpp"

using namespace raytracer;

Background::Background(Color &b_left, Color &t_left, Color &t_right, Color &b_right)
{
    // Corners are assigned clockwise, beginning with bottom left
    corners[0] = b_left;
    corners[1] = t_left;
    corners[2] = t_right;
    corners[3] = b_right;        
}

Color Background::sample(real_value x, real_value y)
{
    // Getting the colors from the corners
    Color c00(corners[0]);
    Color c01(corners[1]);
    Color c10(corners[3]);
    Color c11(corners[2]);

    // Applying bilinear interpolation equation
    Color first_term = c00;
    Color second_term = (c10 - c00) * x;
    Color third_term = (c01 - c00) * y;
    Color fourth_term = (c11 + c00 - (c10 + c01)) * x * y;
    Color bilinear_interpolation = first_term + second_term + third_term + fourth_term;
    
    return bilinear_interpolation;
}