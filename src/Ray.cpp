/**
 * @file        Ray.cpp
 * @author      Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief       This file implements the Ray class. 
 * @version     0.1
 * @date        2019-04-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../include/Ray.h"
#include "Vec3.cpp"

using namespace raytracer;

Point Ray::operator()(real_value t) const { return o + t * d; }