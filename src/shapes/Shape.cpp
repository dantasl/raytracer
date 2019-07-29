/**
 * @file                Shape.cpp
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               Implements the Sphere
 * @version             0.1
 * @date                2019-05-23
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/shapes/Shape.h"

raytracer::Shape::Shape(std::shared_ptr<Material> material)
    : material{material}
    {/* empty */}