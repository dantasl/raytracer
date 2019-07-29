/**
 * @file        Triangle.cpp
 * @author      Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief       This file implements the Triangle class.
 * @version     0.1
 * @date        2019-06-19
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/shapes/Triangle.h"
#include "../Vec3.cpp"

using namespace raytracer;

Triangle::Triangle(std::shared_ptr<Material> m, std::shared_ptr<TriangleMesh> mesh,
                   int tri_id, bool bfc)
    : Shape{m}
    , mesh{mesh}
    , backface_cull{bfc}
{
    v = &mesh->vertex_indices[ 3 * tri_id ];
}

bool Triangle::intersect(const Ray &ray, SurfaceInteration *isect)
{
    // Implements the Möller–Trumbore ray-triangle intersection algorithm
    const float EPSILON = 0.0000001;

    // This will retrieve the vertices of the triangle
    std::tuple<Point, Point, Point> vertices = triangle_vertices();
    Point &vertex_1 = std::get<0>(vertices);
    Point &vertex_2 = std::get<1>(vertices);
    Point &vertex_3 = std::get<2>(vertices);

    // Declarations of necessary variables
    Vector edge_1, edge_2, tvec, pvec, qvec;
    float det, inv_det, u, v, ray_t;

    // Calculates edges
    edge_1 = vertex_2 - vertex_1;
    edge_2 = vertex_3 - vertex_1;

    // Finds pvec and det
    pvec = cross( unit_vector(ray.d), edge_2 );
    det = dot(edge_1, pvec);

    if (backface_cull)
    {
        if (det < EPSILON) return false;

        // Calculate distance from vertex_1 to ray origin
        tvec = ray.o - vertex_1;

        // Calculate the u coordinate and test bounds
        u = dot(tvec, pvec);
        if (u < 0.0 || u > 1.0) return false;

        // Prepare to test v coordinate
        qvec = cross(tvec, edge_1);

        // Calculate v coordinate and test bounds
        v = dot( unit_vector(ray.d), qvec );
        if (v < 0.0 || (u + v) > det) return false;

        // Calculate ray_t, scale parameters, ray intersects triangle
        ray_t = dot(edge_2, qvec);
        inv_det = 1.0 / det;
        ray_t *= inv_det;
        u *= inv_det;
        v *= inv_det;
        // if (ray_t < EPSILON) return false;
    }
    else
    {
        if (det > -EPSILON && det < EPSILON) return false;
        inv_det = 1.0 / det;
        
        // Calculate distance from vertex_1 to ray origin
        tvec = ray.o - vertex_1;

        // Calculate the u coordinate and test bounds
        u = dot(tvec, pvec) * inv_det;
        if (u < 0.0 || u > 1.0) return false;

        // Prepare to test v coordinate
        qvec = cross(tvec, edge_1);

        // Calculate v coordinate and test bounds
        v = dot( unit_vector(ray.d), qvec ) * inv_det;
        if (v < 0.0 || (u + v) > 1.0) return false;

        // Calculate ray_t, ray intersects triangle
        ray_t = dot(edge_2, qvec) * inv_det;
    }
    
    if (ray_t > ray.t_max) return false;

    if (isect != nullptr)
    {
        isect->mat = material.get();
        isect->ray_t = ray_t;
        isect->p = ray(ray_t);
        isect->uv = Point(u, v, 0);
        isect->wo = unit_vector(-1.0 * (ray.d - ray.o));
        //isect->wo = unit_vector(-1.0 * ray.d);

        std::tuple<Vector, Vector, Vector> normals = triangle_normals();
        Point &normal_1 = std::get<0>(normals);
        Point &normal_2 = std::get<1>(normals);
        Point &normal_3 = std::get<2>(normals);
        isect->n = unit_vector( (1 - u - v) * normal_1 + u * normal_2 + v * normal_3 );
    }

    return true;
}

bool Triangle::intersect_p(const Ray &ray)
{
    return this->intersect(ray, nullptr);
}

Boundaries Triangle::boundaries() const
{
    std::tuple<Point, Point, Point> vertices = triangle_vertices();
    Boundaries b(std::get<0>(vertices), std::get<1>(vertices));
    return b.get_union(b, std::get<2>(vertices));
}