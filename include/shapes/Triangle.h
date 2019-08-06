/**
 * @file        Triangle.h
 * @author      Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief       This file defines the Triangle class.
 * @version     0.1
 * @date        2019-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_TRIANGLE_H
#define RAYTRACER_TRIANGLE_H

#include <memory>
#include <tuple>
#include "Shape.h"
#include "TriangleMesh.h"

namespace raytracer
{
    class Triangle: public Shape
    {
        private:
            
            int *v; // Pointer to an index array stored elsewhere (triangle mesh) in memory. 
            std::shared_ptr<TriangleMesh> mesh;
            bool backface_cull; // Set it `true` to turn backface culling.
        
        public:
            
            /**
             * @brief Construct a new Triangle object
             * 
             * @param mesh 
             * @param tri_id 
             * @param bfc 
             */
            Triangle(std::shared_ptr<Material> m, std::shared_ptr<TriangleMesh> mesh,
                     int tri_id, bool bfc=false);

            /**
             * @brief Destroy the Triangle object
             */
            ~Triangle() = default;
            
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
             *                  to determine if the ray intersects or not the triangle.
             * 
             * @param r         The ray to check if the triangle was hit by
             * @return true     If the ray intersect the triangle
             * @return false    If the ray does not intersect the triangle
             */
            bool intersect_p( const Ray &r );

            /**
             * @brief   This creates the boundaries of a triangle.
             * 
             * @return Boundaries 
             */
            Boundaries boundaries() const;

            /**
             * @brief   This will return the tuple of vertices within the TriangleMesh
             * 
             * @return std::tuple<Point, Point, Point> 
             */
            std::tuple<Point, Point, Point> triangle_vertices() const
            {
                Point &v1 = mesh->points[v[0]];
                Point &v2 = mesh->points[v[1]];
                Point &v3 = mesh->points[v[2]];

                return std::make_tuple(v1, v2, v3);
            }

            std::tuple<Vector, Vector, Vector> triangle_normals() const
            {
                Vector &v1 = mesh->normals[v[0]];
                Vector &v2 = mesh->normals[v[1]];
                Vector &v3 = mesh->normals[v[2]];

                return std::make_tuple(v1, v2, v3);
            }
    };
}

#endif // RAYTRACER_TRIANGLE_H