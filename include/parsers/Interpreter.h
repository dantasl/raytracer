/**
 * @file            Interpreter.h
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This file defines a static class for interpreting a XML scene.
 * @version         0.1
 * @date            2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_INTERPRETER_H
#define RAYTRACER_INTERPRETER_H

#include "../Vec3.h"
#include "../cameras/Film.h"
#include "../Background.h"
#include "../cameras/Film.h"
#include "../cameras/Camera.h"
#include "../cameras/OrthoCamera.h"
#include "../cameras/PerspectiveCamera.h"
#include "tinyxml2.h"
#include "../primitives/AggregatePrimitive.h"
#include "../shapes/Sphere.h"
#include "../shapes/TriangleMesh.h"
#include "../shapes/Triangle.h"
#include "../materials/FlatMaterial.h"
#include "../materials/BlinnPhongMaterial.h"
#include "../integrators/FlatIntegrator.h"
#include "../integrators/NormalMapIntegrator.h"
#include "../integrators/DepthIntegrator.h"
#include "../integrators/BlinnPhongIntegrator.h"
#include "../lights/AmbientLight.h"
#include "../lights/PointLight.h"
#include "../lights/DirectionalLight.h"
#include "../lights/Spotlight.h"
#include <vector>
#include <memory>
#include <iterator>
#include <string>
#include <unordered_map>
#include <cctype>
#include <sstream>

namespace raytracer
{
    class Interpreter
    {
        private:
            tinyxml2::XMLDocument scene;
            tinyxml2::XMLNode *pRoot;

        public:
            std::shared_ptr<Camera> camera;
            std::shared_ptr<Background> background;     //!< The interpreter has access to one background
            std::string scene_file;     //!< Path of the scene file
            std::vector<std::shared_ptr<Primitive>> primitives;
            std::vector<std::shared_ptr<Material>> materials;
            std::vector<std::shared_ptr<Light>> lights;
            std::shared_ptr<Integrator> integrator;


            /**
             * @brief               Construct a new Interpreter object
             * 
             * @param scene_file    Path to the scene xml file
             */
            Interpreter(std::string scene_file);

            /**
             * @brief Destroy the Interpreter object
             */
            ~Interpreter();

            /**
             * @brief           Calls all the functions needed to run the interpreter.
             */
            void run();

            /**
             * @brief           Using tinyxml2, parses a xml scene file and interprets
             *                  the background tag.
             */
            void interpret_background();

            /**
             * @brief           Using tinyxml2, parses a xml scene file and interprets
             *                  the camera tag, instantiating an OrthoCamera or PerspectiveCamera.
             */
            void interpret_camera();

            /**
             * @brief           Creates a library of materials, found on scene.
             */
            void interpret_materials();

            /**
             * @brief           Iterates over the list of primitives inside the scene and interprets them.
             */
            void interpret_primitives();

            /**
             * @brief           Read and create the integrator of the scene.
             */
            void interpret_integrators();

            /**
             * @brief           Read and create the lights from the scene.
             */
            void interpret_lights();


    };
}

#endif //RAYTRACER_INTERPRETER_H
