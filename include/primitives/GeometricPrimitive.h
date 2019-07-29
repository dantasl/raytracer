/**
 * @file                GeometricPrimitive.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the Geometric Primitive
 * @version             0.1
 * @date                2019-05-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_GEOMETRICPRIMITIVE_H
#define RAYTRACER_GEOMETRICPRIMITIVE_H

#include "Primitive.h"
#include "../shapes/Shape.h"
#include <memory>

namespace raytracer
{
    class GeometricPrimitive: public Primitive
    {
        private:
            std::shared_ptr<Shape> shape;
            std::shared_ptr<Material> material;
        
        public:

            /**
             * @brief Construct a new Geometric Primitive object
             * 
             * @param s     The shape associated with this primitive
             * @param m     The material of the primitive
             */
            GeometricPrimitive(std::shared_ptr<Shape> s, std::shared_ptr<Material> m)
                : shape{s}
                , material{m}
                {/* empty */}

            /**
             * @brief Destroy the Geometric Primitive object
             */
            ~GeometricPrimitive() = default;

            const Material* get_material() const override
            {
                return material.get(); 
            }

            bool intersect(const Ray &r, SurfaceInteration *si) const
            {
                si->primitive = this;
                return shape->intersect(r, si);
            }

            bool intersect_p( const Ray &r ) const
            {
                return shape->intersect_p(r);
            }

            Boundaries boundaries() const
            {
                return shape->boundaries();
            }
    };
}

#endif // RAYTRACER_GEOMETRICPRIMITIVE_H