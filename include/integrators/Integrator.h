/**
 * @file                Integrator.h
 * @author              Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief               This file defines the base class of all integrators.
 * @version             0.1
 * @date                2019-05-16
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef RAYTRACER_INTEGRATOR_H
#define RAYTRACER_INTEGRATOR_H

#include "../Scene.h"

namespace raytracer
{
    class Integrator
    {
        public:
            Integrator(){}
            virtual void render( const Scene& scene ) = 0;
    };
}

#endif // RAYTRACER_INTEGRATOR_H