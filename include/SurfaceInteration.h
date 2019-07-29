/**
 * @file            SurfaceInteration.h
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           Defines the class that represents the geometry of particular point on a surface
 * @version         0.1
 * @date            2019-04-12
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_SURFACEINTERATION_H
#define RAYTRACER_SURFACEINTERATION_H

#include "Vec3.h"
#include "primitives/Primitive.h"

namespace raytracer
{
    class SurfaceInteration
    {
        public:

            /**
             * @brief       Construct a new Surface Interation object
             * 
             * @param p         Contact point
             * @param n         The surface normal
             * @param wo        Outgoing direction of light
             * @param time      Time of contact 
             * @param uv        Coordinate of hit surface
             * @param pri       Pointer to the primitive
             */
            SurfaceInteration(const Point &p, const Vector &n, const Vector &wo, float time,
                              const Point &uv, Primitive *pri, real_value t)
                : p{p}
                , n{n}
                , wo{wo}
                , time{time}
                , uv{uv}
                , primitive{pri}
                , ray_t{t}
                { /* empty */ }

            /**
             * @brief Construct a new Surface Interation object
             */
            SurfaceInteration() = default;

            /**
             * @brief Construct a new Surface Interation object given a point
             * 
             * @param contact_point 
             */
            SurfaceInteration(const Point &contact_point) : p{contact_point} {}

            /**
             * @brief       Overloading = operator
             * 
             * @param s 
             * @return SurfaceInteration& 
             */
            SurfaceInteration & operator= (const SurfaceInteration &s)
            {
                this->p = s.p;
                this->n = s.n;
                this->wo = s.wo;
                this->time = s.time;
                this->uv = s.uv;
                this->ray_t = s.ray_t;
                this->primitive = s.primitive;
                this->mat = s.mat;
                return *this;
            }

            Point p;                                //!< Contact point.
            Vector n;                               //!< The surface normal.
            Vector wo;                              //!< Outgoing direction of light, which is -ray.
            float time;                             //!< Time of contact.
            Point uv;                               //!< Parametric coordinate (u,v) of the hit surface.
            real_value ray_t;                       //!< The t parameter of the ray where intersection occurred.
            const Primitive *primitive = nullptr;   //!< Pointer to the primitive.
            Material *mat;
    };
}

#endif // RAYTRACER_SURFACEINTERATION_H