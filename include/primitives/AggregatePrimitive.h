/**
 * @file                AggregatePrimitive.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the AggregatePrimitive class.
 * @version             0.1 
 * @date                2019-05-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_AGGREGATEPRIMITIVE_H
#define RAYTRACER_AGGREGATEPRIMITIVE_H

#include "Primitive.h"
#include "../SurfaceInteration.h"
#include <vector>
#include <memory>

namespace raytracer
{
    class AggregatePrimitive : public Primitive
    {
        private:
            std::vector<std::shared_ptr<Primitive>> primitives;

        public:

            /**
             * @brief               Construct a new Aggregate Primitive object
             * 
             * @param primitives    A container with primitives bundled up together
             */
            AggregatePrimitive(std::vector<std::shared_ptr<Primitive>> primitives)
                : primitives{primitives}
                {/* empty */}
            
            /**
             * @brief Destroy the Aggregate Primitive object
             */
            ~AggregatePrimitive() = default;

            /**
             * @override 
             */
            bool intersect(const Ray &r, SurfaceInteration *isect) const
            {
                real_value t_max = std::numeric_limits<real_value>::max();
                real_value t_min = 0;
                bool hit = false;
                SurfaceInteration *isect_min;

                for (const auto p : primitives)
                {
                    bool intersected = p->intersect(r, isect);                  
                    if (intersected && (isect->ray_t < t_max) && (isect->ray_t > t_min))
                    {
                        r.t_max = isect->ray_t;
                        t_max = isect->ray_t;
                        isect_min = isect;
                        hit = true;
                    }
                }

                isect = isect_min;
                return hit;
            }
            
            /**
             * @override 
             */
            bool intersect_p( const Ray &r ) const
            {
                for (const auto p : primitives)
                    if (p->intersect_p(r)) return true;
                return false;
            }
            
            /**
             * @override 
             */
            const Material* get_material() const {}

            /**
             * @brief   This function will iterate over each primitive
             *          within the vector of primitives. Then, it will
             *          generate the boundaries of the whole world, by
             *          calculating the union of all boundaries.
             * 
             * @return Boundaries 
             */
            Boundaries boundaries() const override
            {
                // We begin with the boundaries of the first primitive
                auto b = primitives.front()->boundaries();                
                // Now, we iterate over the remaining primitives
                for(const auto p : primitives)
                    b = b.get_union(b, p->boundaries());
                return b;
            }
    };
}

#endif // RAYTRACER_AGGREGATEPRIMITIVE_H
