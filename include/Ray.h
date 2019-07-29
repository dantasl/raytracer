/**
 * @file        Ray.h
 * @author      Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief       This class defines the abstraction of a Ray.
 * @version     0.1
 * @date        2019-04-06
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_RAY_H
#define RAYTRACER_RAY_H

#include "Vec3.h"
#include <limits>

namespace raytracer
{
    class Ray
    {
        public:
            Point o; //!< Origin
            Vector d; //!< Direction
            mutable real_value t_max = std::numeric_limits<real_value>::max();
            
            /**
             * @brief Construct a new Ray object
             * 
             * @param o     Origin of the Ray
             * @param d     Direction of the Ray
             */
            Ray (const Point& o, const Vector& d) : o{o}, d{d} {/*empty*/}

            /**
             * @brief           Overloading operator so that it returns o + t*d.
             * 
             * @param t         Fractional distance
             * @return Point     The ray at the calculated position
             */
            Point operator()(real_value t) const;

            friend std::ostream& operator<< (std::ostream &os, const Ray &ray){
                os << "[o=(" << ray.o.x() << "," << ray.o.y() << "," << ray.o.z() << ")";
                os << ", d=(" << ray.d.x() << "," << ray.d.y() << "," << ray.d.z() << ")]";
                return os;
            }
    };
}

#endif // RAYTRACER_RAY_H