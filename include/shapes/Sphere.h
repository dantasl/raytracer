/**
 * @file                Sphere.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the abstraction of a Sphere.
 * @version             0.1
 * @date                2019-04-13
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_SPHERE_H
#define RAYTRACER_SPHERE_H

#include "Shape.h"
#include "../Vec3.h"

namespace raytracer
{
    class Sphere: public Shape
    {
        private:
            real_value radius;
            Point center;
            std::string name;
        
        public:
            
            /**
             * @brief Construct a new Sphere object.
             * 
             * @param r     The radius of the sphere.
             * @param c     The center point of the sphere.
             */
            Sphere(std::shared_ptr<Material> m, real_value r, std::string name, Point &c);
            
            /**
             * @brief Destroy the Sphere object
             */
            ~Sphere();

            /**
             * @brief           Given a ray and a surface, checks if they intercept each ohter
             * 
             * @param r         The ray to check if the surface intercepts
             * @param si        The surface to check if the ray intercepts
             * @return true     If there is an interception
             * @return false    If there is not an interception
             */
            bool intersect( const Ray &r, SurfaceInteration *si );

            /**
             * @brief           Given a ray, applies ray-sphere intersection equation
             *                  to determine if the ray intersects or not the sphere.
             * 
             * @param r         The ray to check if the sphere was hit by
             * @return true     If the ray intersect the sphere
             * @return false    If the ray does not intersect the sphere
             */
            bool intersect_p( const Ray &r );

            /**
             * @brief   This creates the boundaries of a sphere.
             * 
             * @return Boundaries 
             */
            Boundaries boundaries() const;
    }; 
}

#endif // RAYTRACER_SPHERE_H