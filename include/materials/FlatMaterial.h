/**
 * @file                FlatMaterial.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the FlatMaterial.
 * @version             0.1
 * @date                2019-05-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_FLATMATERIAL_H
#define RAYTRACER_FLATMATERIAL_H

#include "Material.h"

namespace raytracer
{
    class FlatMaterial : public Material
    {
        private:
            Color diffuse;
        
        public:
            
            /**
             * @brief               Construct a new Flat Material object
             * 
             * @param identifier    The name of the material
             * @param color         The color of the flat material 
             */
            FlatMaterial(std::string identifier, Color color)
                : Material(identifier)
                , diffuse(color)
                {/* empty, as my wallet */}
            
            /**
             * @brief Destroy the Flat Material object
             */
            ~FlatMaterial() = default;

            /**
             * @brief           Get the color object
             * 
             * @return Color    The diffuse color of this material.
             */
            Color kd() const { return diffuse; }
    };
}

#endif // RAYTRACER_FLATMATERIAL_H
