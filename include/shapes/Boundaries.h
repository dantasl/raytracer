/**
 * @file                Boundaries.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the Boundaries class
 * @version             0.1
 * @date                2019-06-05
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_BOUNDARIES_H
#define RAYTRACER_BOUNDARIES_H

#include "../Vec3.h"
#include <limits>

namespace raytracer
{
    class Boundaries
    {
        public:
            Point p_min, p_max;
    
            Boundaries()
            {
                real_value n_min = std::numeric_limits<real_value>::min();
                real_value n_max = std::numeric_limits<real_value>::max();
                p_min = Point(n_max, n_max, n_max);
                p_max = Point(n_min, n_min, n_min);
            }

            Boundaries(const Point &p)
                : p_min{p}
                , p_max{p}
                {/* empty */}
            
            Boundaries(const Point &p1, const Point &p2)
            {
                // Calculates the minimum within both points
                Point min_point(
                    std::min( p1.x(), p2.x() ),
                    std::min( p1.y(), p2.y() ),
                    std::min( p1.z(), p2.z() )
                );

                // Calculates the maximum within both points
                Point max_point(
                    std::max( p1.x(), p2.x() ),
                    std::max( p1.y(), p2.y() ),
                    std::max( p1.z(), p2.z() )
                );

                p_min = min_point;
                p_max = max_point;
            }

            const Point& operator[](int i) const
            {
                if (i == 0) return p_min;
                if (i == 1) return p_max;
            }

            Point& operator[](int i)
            {
                if (i == 0) return p_min;
                if (i == 1) return p_max;
            }

            Point corner(int c) const
            {
                return Point(
                    (*this)[(c & 1)].x(),
                    (*this)[(c & 2)].y(),
                    (*this)[(c & 4)].z()
                );
            }

            Boundaries get_union(const Boundaries &b, const Point &p)
            {
                return Boundaries
                (
                    Point (
                        std::min(b.p_min.x(), p.x()),
                        std::min(b.p_min.y(), p.y()),
                        std::min(b.p_min.z(), p.z())
                    ),
                    Point (
                        std::max(b.p_min.x(), p.x()),
                        std::max(b.p_min.y(), p.y()),
                        std::max(b.p_min.z(), p.z())
                    )
                );
            }

            Boundaries get_union(const Boundaries &b1, const Boundaries &b2)
            {
                return Boundaries (
                    Point (
                        std::min(b1.p_min.x(), b2.p_min.x()),
                        std::min(b1.p_min.y(), b2.p_min.y()),
                        std::min(b1.p_min.z(), b2.p_min.z())
                    ),
                    Point (
                        std::max(b1.p_max.x(), b2.p_max.x()),
                        std::max(b1.p_max.y(), b2.p_max.y()),
                        std::max(b1.p_max.z(), b2.p_max.z())
                    )
                );
            }

            Boundaries get_intersection(const Boundaries &b1, const Boundaries &b2)
            {
                return Boundaries (
                    Point (
                        std::max(b1.p_min.x(), b2.p_min.x()),
                        std::max(b1.p_min.y(), b2.p_min.y()),
                        std::max(b1.p_min.z(), b2.p_min.z())
                    ),
                    Point (
                        std::min(b1.p_max.x(), b2.p_max.x()),
                        std::min(b1.p_max.y(), b2.p_max.y()),
                        std::min(b1.p_max.z(), b2.p_max.z())
                    )
                );        
            }

            bool overlaps(const Boundaries &b1, const Boundaries &b2)
            {
                bool x = (b1.p_max.x() >= b2.p_min.x()) && (b1.p_min.x() <= b2.p_max.x());
                bool y = (b1.p_max.y() >= b2.p_min.y()) && (b1.p_min.y() <= b2.p_max.y());
                bool z = (b1.p_max.z() >= b2.p_min.z()) && (b1.p_min.z() <= b2.p_max.z());
                return (x && y && z);
            }

            bool inside(const Point &p, const Boundaries &b) const;

            bool inside_exclusive(const Point &p, const Boundaries &b)
            {
                return (
                    p.x() >= b.p_min.x() && p.x() < b.p_max.x() &&
                    p.y() >= b.p_min.y() && p.y() < b.p_max.y() &&
                    p.z() >= b.p_min.z() && p.z() < b.p_max.z()
                );
            }

            Boundaries expand(const Boundaries &b, real_value delta);

            Vector diagonal() const;

            real_value surface_area() const;

            real_value volume() const
            {
                Vector d = diagonal();
                return d.x() * d.y() * d.z(); 
            }

            int maximum_extent() const
            {
                Vector d = diagonal();
                if (d.x() > d.y() && d.x() > d.z()) return 0; 
                else if (d.y() > d.z()) return 1;
                else return 2;
            }
            
            Vector offset(const Point &p) const; 

            void bounding_sphere(Point *center, float *radius);
    };
}

#endif // RAYTRACER_BOUNDARIES_H