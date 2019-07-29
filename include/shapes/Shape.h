/**
 * @file            Shape.h
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This class defines the abstractoin of a shape.
 * @version         0.1
 * @date            2019-05-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_SHAPE_H
#define RAYTRACER_SHAPE_H

#include "../Ray.h"
#include "../SurfaceInteration.h"
#include "../materials/Material.h"
#include "Boundaries.h"
#include <memory>

namespace raytracer
{
    class Shape
    {
        protected:
            int identifier;
            std::shared_ptr<Material> material;
        
        public:

            /**
             * @brief               Construct a new Shape object
             * 
             * @param material      The material of the shape 
             */
            Shape(std::shared_ptr<Material> material);

            /**
             * @brief Destroy the Shape object
             */
            virtual ~Shape() = default;

            /**
             * @brief           Given a ray and a surface, checks if they intercept each ohter
             * 
             * @param r         The ray to check if the surface intercepts
             * @param si        The surface to check if the ray intercepts
             * @return true     If there is an interception
             * @return false    If there is not an interception
             */
            virtual bool intersect( const Ray &r, SurfaceInteration *si) = 0;
            
            /**
             * @brief           Given a certain ray, checks if the ray intersects the primitive
             * 
             * @param r         The ray to check if the primitive was hit by
             * @return true     If the ray intersects the primitive
             * @return false    If the ray does not intersects the primitive
             */
            virtual bool intersect_p( const Ray &r ) = 0;

            /**
             * @brief   A method to return the boundaries of the shape.
             * 
             * @return  Boundaries 
             */
            virtual Boundaries boundaries() const = 0;
    };
}

#endif // RAYTRACER_SHAPE_H
