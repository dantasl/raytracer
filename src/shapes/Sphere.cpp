/**
 * @file                Sphere.cpp
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file implements the abstraction of a Sphere.
 * @version             0.1
 * @date                2019-04-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/shapes/Sphere.h"
#include "../Vec3.cpp"

using namespace raytracer;

Sphere::~Sphere() {/* empty */};

Sphere::Sphere(std::shared_ptr<Material> m, real_value r, std::string name, Point &c)
    : Shape(m)
    , radius(r)
    , center(c)
    , name(name)
    {/* empty */}

bool Sphere::intersect(const Ray &ray, SurfaceInteration *isect)
{
    Vector oc = ray.o - this->center;

    real_value a = dot(ray.d, ray.d);
    real_value b = 2.0 * dot(oc, ray.d);
    real_value c = dot(oc,oc) - (this->radius * this->radius);        
    real_value delta = (b * b) - (4.0 * a * c);
    if (delta < 0.0) return false;

    real_value x_prime = (-b + sqrt(delta)) / (2 * a);
    real_value x_double_prime = (-b - sqrt(delta)) / (2 * a);
    real_value x_min = fmin(x_prime, x_double_prime);
    if (x_min > ray.t_max || x_min < 0) return false;

    // Fills the parameters of the surface interation
    if (isect != nullptr)
    {
        isect->mat = material.get();
        isect->ray_t = x_min;
        isect->p = ray(x_min);
        isect->n = unit_vector(2.0 * (isect->p - this->center));
        isect->wo = unit_vector(-1.0 * (ray.d - ray.o));
        isect->p += (0.001 * isect->n); 
    }
        
    return true;               
}

bool Sphere::intersect_p( const Ray &ray )
{
    Vector oc = ray.o - this->center;
    real_value a = dot(ray.d, ray.d);
    real_value b = 2.0 * dot(oc, ray.d);
    real_value c = dot(oc,oc) - (this->radius * this->radius);        
    real_value delta = (b * b) - (4.0 * a * c);
    return delta >= 0.0;
}

Boundaries Sphere::boundaries() const
{
    Vector radius_vector{radius, radius, radius};
    return Boundaries(
        center - radius_vector,
        center + radius_vector
    );
}