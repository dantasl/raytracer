/**
 * @file            Vec3.h
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           The class Vec3 is defined here. Code inspired on Peter Shirley's Ray Tracing in One Weekend.
 * @version         0.1
 * @date            2019-03-28
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_VEC3_H
#define RAYTRACER_VEC3_H

#include <math.h>
#include <stdlib.h>
#include <iostream>

namespace raytracer
{
    typedef float real_value;
    
    class Vec3
    {
        public:
            real_value e[3];
            
            Vec3(real_value e0 = 0, real_value e1 = 0, real_value e2 = 0)
            {
                e[0] = e0;
                e[1] = e1;
                e[2] = e2;
            }
            
            inline real_value x() const { return e[0]; }
            inline real_value y() const { return e[1]; }
            inline real_value z() const { return e[2]; }
            inline real_value r() const { return e[0]; }
            inline real_value g() const { return e[1]; }
            inline real_value b() const { return e[2]; }

            inline const Vec3& operator+() const { return *this; }
            inline Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
            inline real_value operator[](int i) const { return e[i]; }
            inline real_value& operator[](int i) { return e[i]; }

            inline Vec3& operator+=(const Vec3 &v2);
            inline Vec3& operator-=(const Vec3 &v2);
            inline Vec3& operator*=(const Vec3 &v2);
            inline Vec3& operator/=(const Vec3 &v2);
            inline Vec3& operator*=(const real_value t);
            inline Vec3& operator/=(const real_value t);

            inline void make_unit_vector()
            {
                real_value k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
                e[0] *= k;
                e[1] *= k;
                e[2] *= k;
            }
            inline real_value length() const
            {
                return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
            }
            inline real_value squared_length() const
            {
                return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
            }
    };

    typedef Vec3 Color;
    typedef Vec3 Point;
    typedef Vec3 Vector;
}

#endif // RAYTRACER_VEC3_H
