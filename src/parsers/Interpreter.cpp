/**
 * @file            Interpreter.cpp
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This file implements a static class for interpreting a XML scene file.
 * @version         0.1
 * @date            2019-04-01
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/parsers/Interpreter.h"
#include "../../include/primitives/GeometricPrimitive.h"

using namespace tinyxml2;

raytracer::Interpreter::Interpreter(std::string scene_file)
    : scene_file{scene_file}
{
    // Extracting Node element from XML and checking if it exists
    scene.LoadFile(scene_file.c_str());
    pRoot = scene.FirstChildElement("raytracer");
    background = std::shared_ptr<Background>(new Background);

    if (pRoot == nullptr) return; // Error while loading scene file.
}

raytracer::Interpreter::~Interpreter()
{
    // empty for now, but you can place the freeing of pointers here
}

void raytracer::Interpreter::run()
{
    interpret_background();
    interpret_camera();
    interpret_materials();
    interpret_primitives();
    interpret_integrators();
    interpret_lights();
    std::cout << "Finished parsing!" << std::endl;
}

void raytracer::Interpreter::interpret_background()
{
    XMLElement *pScene = pRoot->FirstChildElement("scene");
    std::vector<Color> colors;
    Color aux_color;
    real_value r, g, b;    

    XMLElement *pBackground = pScene->FirstChildElement("background");
    if (pBackground == nullptr) return;

    for (auto color(pBackground->FirstChildElement()); color != nullptr;
        color = color->NextSiblingElement())
    {
        r = std::stoi(color->Attribute("r"));
        g = std::stoi(color->Attribute("g"));
        b = std::stoi(color->Attribute("b"));
        colors.push_back(Color(r, g, b));
    }

    // Assigning colors
    for (auto i(0u); i < 4; ++i)
    {
        if (i < colors.size()) aux_color = colors[i];
        background->corners[i] = aux_color;
    }
}

void raytracer::Interpreter::interpret_camera()
{    
    int width, height;
    Point position, target;
    Vector vup;
    std::string type, filename;
    real_value left, right, bottom, top, fovy, aspect, fdistance;

    XMLElement *pCamera = pRoot->FirstChildElement("camera");
    if (pCamera == nullptr) return;

    std::cout << "Beginning to parse the Camera from the scene." << std::endl;

    // Getting the retina configuration
    width = std::stoi( pCamera->FirstChildElement("width")->Attribute("value") );
    height = std::stoi( pCamera->FirstChildElement("height")->Attribute("value") );

    std::cout << "Camera Width: " << width << std::endl;
    std::cout << "Camera Height: " << height << std::endl;

    // Getting position, target and up
    position.e[0] = std::stoi(pCamera->FirstChildElement("position")->Attribute("x"));
    position.e[1] = std::stoi(pCamera->FirstChildElement("position")->Attribute("y"));
    position.e[2] = std::stoi(pCamera->FirstChildElement("position")->Attribute("z"));

    std::cout << "Position of the Camera: ";
    std::cout << "(" << position.e[0] << "," << position.e[1] << "," << position.e[2] << ")" << std::endl;

    target.e[0] = std::stoi(pCamera->FirstChildElement("target")->Attribute("x"));
    target.e[1] = std::stoi(pCamera->FirstChildElement("target")->Attribute("y"));
    target.e[2] = std::stoi(pCamera->FirstChildElement("target")->Attribute("z"));

    std::cout << "Target of the Camera: ";
    std::cout << "(" << target.e[0] << "," << target.e[1] << "," << target.e[2] << ")" << std::endl;

    vup.e[0] = std::stoi(pCamera->FirstChildElement("up")->Attribute("x"));
    vup.e[1] = std::stoi(pCamera->FirstChildElement("up")->Attribute("y"));
    vup.e[2] = std::stoi(pCamera->FirstChildElement("up")->Attribute("z"));

    std::cout << "Vector Up of the Camera: ";
    std::cout << "(" << vup.e[0] << "," << vup.e[1] << "," << vup.e[2] << ")" << std::endl;

    filename = pCamera->FirstChildElement("img_file")->Attribute("name");
    std::cout << "Filename: " << filename << std::endl;

    // Creating the Film object
    std::shared_ptr<Film> film(new Film(width, height, filename));

    // Getting type of camera and instantiating it
    type = pCamera->Attribute("type");
    if (type.compare("orthographic") == 0)
    {
        left = std::atof(pCamera->FirstChildElement("vpdim")->Attribute("l"));
        right = std::atof(pCamera->FirstChildElement("vpdim")->Attribute("r"));
        bottom = std::atof(pCamera->FirstChildElement("vpdim")->Attribute("b"));
        top = std::atof(pCamera->FirstChildElement("vpdim")->Attribute("t"));

        std::cout << "Camera Type: Ortographic. Dimensions: ";
        std::cout << "Left: " << left << " Right: " << right << " Bottom: " << bottom << " Top: " << top << std::endl;
        
        camera = std::shared_ptr<Camera>(new OrthoCamera(width, height, position, target, vup, film, left, right, bottom, top));
    }
    else if (type.compare("perspective") == 0)
    {
        fovy = std::atof(pCamera->FirstChildElement("fovy")->Attribute("value"));
        aspect = std::atof(pCamera->FirstChildElement("aspect")->Attribute("value"));
        fdistance = std::atof(pCamera->FirstChildElement("fdistance")->Attribute("value"));

        std::cout << "Camera Type: Perspective. Fovy: " << fovy << " Aspect: " << aspect << " Fdistance: " << fdistance << std::endl;

        camera = std::shared_ptr<Camera>(new PerspectiveCamera(width, height, position, target, vup, film, fovy, aspect, fdistance));
    }
}

void raytracer::Interpreter::interpret_materials()
{
    XMLElement *pScene = pRoot->FirstChildElement("scene");
    XMLElement *pDiffuse, *pAmbient, *pSpecular;
    std::string mat_type, mat_name;
    real_value r, g, b, glossiness;

    for (auto material(pScene->FirstChildElement("material")); material != nullptr;
         material = material->NextSiblingElement())
    {
        mat_type = material->Attribute("type");
        mat_name = material->Attribute("name");
        if (mat_type.compare("flat") == 0)
        {
            pDiffuse = material->FirstChildElement("diffuse");
            r = std::stoi(pDiffuse->Attribute("r"));
            g = std::stoi(pDiffuse->Attribute("g"));
            b = std::stoi(pDiffuse->Attribute("b"));
            Color mat_color(r, g, b);
            std::shared_ptr<Material> flat_mat(new FlatMaterial(mat_name, mat_color));
            materials.push_back(flat_mat);
        }
        else if (mat_type.compare("blinn") == 0)
        {
            glossiness = std::atof(material->FirstChildElement("glossiness")->Attribute("value"));
            pAmbient = material->FirstChildElement("ambient");
            Point ka(
                std::atof(pAmbient->Attribute("r")),
                std::atof(pAmbient->Attribute("g")),
                std::atof(pAmbient->Attribute("b"))
            );

            pDiffuse = material->FirstChildElement("diffuse");
            Point kd(
                std::atof(pDiffuse->Attribute("r")),
                std::atof(pDiffuse->Attribute("g")),
                std::atof(pDiffuse->Attribute("b"))
            );

            pSpecular = material->FirstChildElement("specular");
            Point ks(
                std::atof(pSpecular->Attribute("r")),
                std::atof(pSpecular->Attribute("g")),
                std::atof(pSpecular->Attribute("b"))
            );
            
            // Creating the BlinnMaterial
            std::shared_ptr<Material> blinn_mat(
                new BlinnPhongMaterial(mat_name, ka, kd, ks, glossiness)
            );

            // Inserting new material on vector            
            materials.push_back(blinn_mat);
        }
    }
}

void raytracer::Interpreter::interpret_primitives()
{
    XMLElement *pScene = pRoot->FirstChildElement("scene");
    std::string type, name, mat_name;
    real_value radius, x, y, z;

    std::cout << "Beginning to read primitives..." << std::endl;

    for (auto object(pScene->FirstChildElement("object")); object != nullptr;
        object = object->NextSiblingElement("object"))
    {
        type = object->Attribute("type");
        name = object->Attribute("name");
        mat_name = object->Attribute("material");
        std::shared_ptr<Material> obj_mat;

        // Before moving forwards, we must get the material
        for (auto m : materials)
        {
            if (m->get_identifier().compare(mat_name) == 0)
                obj_mat = m;
        }

        std::cout << "Found " << type << " with name " << name << " of material " << mat_name << std::endl;

        if (type.compare("sphere") == 0)
        {
            radius = std::atof( object->FirstChildElement("radius")->Attribute("value") );
            x = std::atof( object->FirstChildElement("center")->Attribute("x") );
            y = std::atof( object->FirstChildElement("center")->Attribute("y") );
            z = std::atof( object->FirstChildElement("center")->Attribute("z") );
            Point p(x, y, z);
            std::shared_ptr<Shape> sphere(new Sphere(obj_mat, radius, name, p));
            std::shared_ptr<Primitive> primitive(new GeometricPrimitive(sphere, obj_mat));
            this->primitives.push_back(primitive);
        }
        else if (type.compare("trianglemesh") == 0)
        {
            int ntriangles = std::atoi( object->FirstChildElement("ntriangles")->Attribute("value") );
            
            std::string str_indices = object->FirstChildElement("indices")->Attribute("value");
            std::vector<int> indices;
            for (auto c: str_indices)
                if (!isspace(c)) indices.push_back(c - '0');
            
            std::string str_vertices = object->FirstChildElement("vertices")->Attribute("value");
            std::vector<Point> vertices;
            std::istringstream vertices_stream(str_vertices);
            std::vector<float> aux_vector;
            float temp;
            while( vertices_stream >> temp ) aux_vector.push_back(temp);
            for (int i = 0; i < aux_vector.size(); i += 3)
                vertices.push_back(Point(aux_vector[i], aux_vector[i + 1], aux_vector[i + 2]));

            std::string str_normals = object->FirstChildElement("normals")->Attribute("value");
            std::istringstream normals_stream(str_normals);
            std::vector<Vector> normals;
            aux_vector.clear();
            while( normals_stream >> temp ) aux_vector.push_back(temp);
            for (int i = 0; i < aux_vector.size(); i += 3)
                normals.push_back(Vector(aux_vector[i], aux_vector[i + 1], aux_vector[i + 2]));

            std::string str_uv = object->FirstChildElement("uv")->Attribute("value");
            std::vector<Point> uvs;
            std::istringstream uv_stream(str_uv);
            aux_vector.clear();
            while( uv_stream >> temp ) aux_vector.push_back(temp);
            for (int i = 0; i < aux_vector.size(); i += 2)
                uvs.push_back(Point(aux_vector[i], aux_vector[i + 1], 0));

            std::shared_ptr<TriangleMesh> mesh(
                new TriangleMesh(
                    ntriangles, indices.data(), (int) vertices.size(), vertices.data(), normals.data(), uvs.data()
                )
            );

            // Adding the new triangles to the primitives
            for (int i(0); i < ntriangles; ++i)
            {
                std::shared_ptr<Shape> triangle(new Triangle(obj_mat, mesh, i));
                std::shared_ptr<Primitive> primitive(new GeometricPrimitive(triangle, obj_mat));
                this->primitives.push_back(primitive);
            }
        } 
    }
}

void raytracer::Interpreter::interpret_integrators()
{
    std::cout << "Beginning to read integrator..." << std::endl;
    
    XMLElement *pRunning = pRoot->FirstChildElement("running");
    XMLElement *pIntegrator = pRunning->FirstChildElement("integrator");
    XMLElement *pColor;
    std::string integrator_type = pIntegrator->Attribute("type");

    std::shared_ptr<Sampler> sampler(new Sampler());

    if (integrator_type.compare("flat") == 0)
    {        
        integrator = std::shared_ptr<Integrator>(new FlatIntegrator(camera, sampler));              
    }
    else if (integrator_type.compare("normal_map") == 0)
    {
        integrator = std::shared_ptr<Integrator>(new NormalMapIntegrator(camera, sampler));
    }
    else if (integrator_type.compare("depth") == 0)
    {
        pColor = pIntegrator->FirstChildElement("near_color");
        int r = std::stoi(pColor->Attribute("r"));
        int g = std::stoi(pColor->Attribute("g"));
        int b = std::stoi(pColor->Attribute("b"));
        Color near_color(r, g, b);

        pColor = pIntegrator->FirstChildElement("far_color");
        r = std::stoi(pColor->Attribute("r"));
        g = std::stoi(pColor->Attribute("g"));
        b = std::stoi(pColor->Attribute("b"));
        Color far_color(r, g, b);

        integrator = std::shared_ptr<Integrator>(new DepthIntegrator(camera, sampler, near_color, far_color));
    }
    else if (integrator_type.compare("blinn_phong") == 0)
    {
        integrator = std::shared_ptr<Integrator>(new BlinnPhongIntegrator(camera, sampler));
    }
}

void raytracer::Interpreter::interpret_lights()
{
    std::cout << "Beginning to read lights..." << std::endl;
    
    XMLElement *pScene = pRoot->FirstChildElement("scene");
    XMLElement *pIntensity, *pPosition, *pPointAt;
    std::string light_type;
    double r, g, b, cutoff, falloff;

    for (auto light(pScene->FirstChildElement("light")); light != nullptr;
         light = light->NextSiblingElement())
    {
        light_type = light->Attribute("type");
        if (light_type.compare("ambient") == 0)
        {
            pIntensity = light->FirstChildElement("intensity");
            r = std::atof(pIntensity->Attribute("r"));
            g = std::atof(pIntensity->Attribute("g"));
            b = std::atof(pIntensity->Attribute("b"));
            Color intensity(r, g, b);
            lights.push_back(std::shared_ptr<Light>(new AmbientLight(intensity)));
        }
        else if (light_type.compare("point") == 0)
        {
            pIntensity = light->FirstChildElement("intensity");
            r = std::atof(pIntensity->Attribute("r"));
            g = std::atof(pIntensity->Attribute("g"));
            b = std::atof(pIntensity->Attribute("b"));
            Color i(r, g, b);

            pPosition = light->FirstChildElement("position");
            r = std::atof(pPosition->Attribute("x"));
            g = std::atof(pPosition->Attribute("y"));
            b = std::atof(pPosition->Attribute("z"));
            Point p(r, g, b);
            lights.push_back(std::shared_ptr<Light>(new PointLight(i, p)));
        }
        else if (light_type.compare("directional") == 0)
        {
            pIntensity = light->FirstChildElement("intensity");
            r = std::atof(pIntensity->Attribute("r"));
            g = std::atof(pIntensity->Attribute("g"));
            b = std::atof(pIntensity->Attribute("b"));
            Color i(r, g, b);

            pPosition = light->FirstChildElement("direction");
            r = std::atof(pPosition->Attribute("x"));
            g = std::atof(pPosition->Attribute("y"));
            b = std::atof(pPosition->Attribute("z"));
            Point p(r, g, b);
            lights.push_back(std::shared_ptr<Light>(new DirectionalLight(i, p)));
        }
        else if (light_type.compare("spot") == 0)
        {
            pIntensity = light->FirstChildElement("intensity");
            r = std::atof(pIntensity->Attribute("r"));
            g = std::atof(pIntensity->Attribute("g"));
            b = std::atof(pIntensity->Attribute("b"));
            Color i(r, g, b);

            pPosition = light->FirstChildElement("position");
            r = std::atof(pPosition->Attribute("x"));
            g = std::atof(pPosition->Attribute("y"));
            b = std::atof(pPosition->Attribute("z"));
            Point p(r, g, b);

            pPointAt = light->FirstChildElement("point_at");
            r = std::atof(pPointAt->Attribute("x"));
            g = std::atof(pPointAt->Attribute("y"));
            b = std::atof(pPointAt->Attribute("z"));
            Point at(r, g, b);

            cutoff = std::atof(light->FirstChildElement("cutoff")->Attribute("value"));
            falloff = std::atof(light->FirstChildElement("falloff")->Attribute("value"));

            lights.push_back(std::shared_ptr<Light>(new Spotlight(i, p, at, falloff, cutoff)));
        }
    }
}