/**
 * @file                BlinnPhongMaterial.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the Blinn Phong Material.
 * @version             0.1
 * @date                2019-05-31
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_BLINN_PHONG_MATERIAL_H
#define RAYTRACER_BLINN_PHONG_MATERIAL_H

#include "Material.h"

namespace raytracer
{
    class BlinnPhongMaterial: public Material
    {
        private:
            Point ambient_coefficient;
            Point diffuse_coefficient;
            Point specular_coefficient;
            real_value glossiness_expoent;
        
        public:
            
            /**
             * @brief Construct a new Blinn Phong Material object
             * 
             * @param id        Identifier of the material
             * @param ka        The ambient coefficient
             * @param kd        The diffuse coefficient
             * @param ks        The specular coefficient
             * @param ge        The glossiness expoent
             */
            BlinnPhongMaterial(std::string id, Point &ka, Point &kd, Point &ks, real_value ge)
                : Material{id}
                , ambient_coefficient{ka}
                , diffuse_coefficient{kd}
                , specular_coefficient{ks}
                , glossiness_expoent{ge}
                {/* empty */}
            
            /**
             * @brief Destroy the Blinn Phong Material object
             */
            ~BlinnPhongMaterial() = default;

            inline Point ka() const { return ambient_coefficient; }
            inline Point kd() const { return diffuse_coefficient; }
            inline Point ks() const { return specular_coefficient; }
            inline real_value glossiness() const { return glossiness_expoent; }
    };
}

#endif // RAYTRACER_BLINN_PHONG_MATERIAL_H