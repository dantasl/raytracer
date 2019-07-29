/**
 * @file                Material.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the abstraction of a material. 
 * @version             0.1
 * @date                2019-05-14
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_MATERIAL_H
#define RAYTRACER_MATERIAL_H

#include <string>
#include "../Vec3.h"

namespace raytracer
{
    class Material
    {
        private:
            std::string identifier;
        
        public:
            
            /**
             * @brief               Construct a new Material object
             * 
             * @param identifier    The name of the material.
             */
            Material(std::string identifier) : identifier(identifier) {}

            /**
             * @brief Construct a new Material object
             */
            Material() = default;

            /**
             * @brief Destroy the Material object
             */
            virtual ~Material() = default;

            /**
             * @brief Get the identifier object
             * 
             * @return std::string
             */
            std::string get_identifier() { return identifier; }
    };
}

#endif // RAYTRACER_MATERIAL_H
