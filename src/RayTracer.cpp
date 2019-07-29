/**
 * @file            RayTracer.cpp
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This is the main class, that runs the raytracer loop. 
 * @version         0.1
 * @date            2019-04-09
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../include/parsers/Interpreter.h"
#include "../include/Scene.h"
#include "../include/integrators/SampleIntegrator.h"

using namespace raytracer;

void init_engine(const char* filename);
void run();

// === The 3 global objects.
std::shared_ptr<Camera> g_camera; // The single camera object.
std::shared_ptr<Scene> g_scene;   // The scene.
std::shared_ptr<Integrator> g_integrator; // The integrator.

int main(int argc, char *argv[])
{
    init_engine(argv[1]);
    run();   
}

void init_engine(const char* filename)
{
    // [1] Parser and load scene file
    // Load background info.
    // Load Film info.
    // Load Camera info and creates the global camera object.
    Interpreter interpreter(filename);
    interpreter.run();

    // [2] Instantiate the Camera and Integrator objects.
    g_camera = interpreter.camera;
    g_integrator = std::shared_ptr<Integrator>(interpreter.integrator);

    // [3] Create the Scene
    // Load the primitives from the Interpreter
    // Instantiate Scene object
    std::shared_ptr<Primitive> aggregate(new AggregatePrimitive(interpreter.primitives));
    g_scene = std::shared_ptr<Scene>(
        new Scene(aggregate, interpreter.lights, interpreter.background)
    );
}

void run(void)
{
    g_integrator->render(*g_scene); // Activate the main loop
    g_camera->get_film()->write_image();
}
