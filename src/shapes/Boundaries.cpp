/**
 * @file            Boundaries.cpp
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This file implements the Boundaries 
 * @version         0.1
 * @date            2019-06-07
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/shapes/Boundaries.h"
#include "../Vec3.cpp"

using namespace raytracer;

Boundaries Boundaries::expand(const Boundaries &b, real_value delta)
{
    return Boundaries (
        b.p_min - Vector{delta, delta, delta},
        b.p_max + Vector{delta, delta, delta}
    );
}

Vector Boundaries::diagonal() const { return p_max - p_min; }

Vector Boundaries::offset(const Point &p) const
{
    Vector o = p - p_min;
    if (p_max.x() > p_min.x()) o.e[0] /= p_max.x() - p_min.x();
    if (p_max.y() > p_min.y()) o.e[1] /= p_max.y() - p_min.y();
    if (p_max.z() > p_min.z()) o.e[2] /= p_max.z() - p_min.z();
    return o;
}

bool Boundaries::inside(const Point &p, const Boundaries &b) const
{
    return (p.x() >= b.p_min.x() && p.x() <= b.p_max.x() &&
            p.y() >= b.p_min.y() && p.y() <= b.p_max.y() &&
            p.z() >= b.p_min.z() && p.z() <= b.p_max.z());
}

real_value Boundaries::surface_area() const
{
    Vector d = diagonal();
    return 2 * (d.x() * d.y() + d.x() * d.z() + d.y() * d.z());
}

void Boundaries::bounding_sphere(Point *center, float *radius)
{
    *center = (p_min + p_max) / 2; 
    *radius = inside(*center, *this) ? distance(p_max, *center) : 0;
}