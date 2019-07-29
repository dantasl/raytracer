/**
 * @file            Primitive.h
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This file describes the abstract class to represent any surface that might be hit by a ray.
 * @version         0.1
 * @date            2019-04-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_PRIMITIVE_H
#define RAYTRACER_PRIMITIVE_H

#include "../Ray.h"
#include "../materials/Material.h"
#include "../shapes/Boundaries.h"

namespace raytracer
{
    class SurfaceInteration;
    class Primitive
    {
        public:
            /**
             * @brief Construct a new Primitive object
             */
            Primitive() = default;

            /**
             * @brief Destroy the Primitive object
             */
            virtual ~Primitive() = default;

            /**
             * @brief                       Get the material of the primitive
             * 
             * @return const Material*      The material of the primitive
             */
            virtual const Material* get_material() const = 0;

            /**
             * @brief           Given a ray and a surface, checks if they intercept each ohter
             * 
             * @param r         The ray to check if the surface intercepts
             * @param si        The surface to check if the ray intercepts
             * @return true     If there is an interception
             * @return false    If there is not an interception
             */
            virtual bool intersect( const Ray &r, SurfaceInteration *isect) const = 0;
            
            /**
             * @brief           Given a certain ray, checks if the ray intersects the primitive
             * 
             * @param r         The ray to check if the primitive was hit by
             * @return true     If the ray intersects the primitive
             * @return false    If the ray does not intersects the primitive
             */
            virtual bool intersect_p( const Ray &r ) const = 0;

            /**
             * @brief   Pure virtual method that must be implemented in order
             *          to get the boundaries of a shape.
             * 
             * @return Boundaries 
             */
            virtual Boundaries boundaries() const = 0;
    };      

}

#endif // RAYTRACER_PRIMITIVE_H
