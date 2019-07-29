/**
 * @file        TriangleMesh.h
 * @author      Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief       This file defines the TriangleMesh structure.
 * @version     0.1
 * @date        2019-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_TRIANGLE_MESH_H
#define RAYTRACER_TRIANGLE_MESH_H

#include <vector>
#include <memory>
#include "../Vec3.h"

namespace raytracer
{
    struct TriangleMesh
    {
        const int n_triangles;
        const int n_vertices;
        std::vector<int> vertex_indices;
        std::unique_ptr<Point[]> points;   //!< The 3D geometric coordinates
        std::unique_ptr<Vector[]> normals; //!< The 3D normals.
        std::unique_ptr<Point[]> uv;       //!< The 2D texture coordinages (might be 3D, if necessary).
        
        // Regular constructor
        TriangleMesh(int n_tri, const int *indices, int n_vertices, const Point *p,
                     const Vector *n, const Point *uv)
            : n_triangles{n_tri}
            , n_vertices{n_vertices}
            , vertex_indices{indices, indices + 3 * n_triangles}
        {
            points.reset(new Point[n_vertices]);
            for (int i = 0; i < n_vertices; ++i) points[i] = p[i];
            
            normals.reset(new Vector[n_vertices]);
            for (int i = 0; i < n_vertices; ++i) normals[i] = n[i];
        }
    };
}

#endif // RAYTRACER_TRIANGLE_MESH_H