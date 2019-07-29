/**
 * @file            Film.cpp
 * @author          Lucas Gomes Dantas (dantaslucas@ufrn.edu.br)
 * @brief           This files implements the abstraction of a Film.
 * @version         0.1
 * @date            2019-03-27
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../../include/cameras/Film.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../include/parsers/stb_image_write.h"

using namespace raytracer;

void Film::write_image()
{
    std::size_t pos = filename.find(".");
    std::string extension = filename.substr(pos);
    
    if (extension.compare(".png") == 0)
    {
        stbi_flip_vertically_on_write(1);
        stbi_write_png(filename.c_str(), width, height, 3, get_image(), width * 3);
    }
    else if(extension.compare(".ppm") == 0)
    {
        std::ofstream image;
        image.open(filename);
        component_t *sketches = get_image();

        image << "P3" << "\n";
        image << width << " " << height << "\n" << 255 << "\n";

        for (int y = height - 1; y >= 0; y--)
        {
            for (uint x = 0; x < width; ++x)
            {
                auto pixel_init(y * (width * 3) + (x * 3));
                image << static_cast<unsigned>( sketches[ pixel_init ] ) << " ";
                image << static_cast<unsigned>( sketches[ pixel_init + 1 ] ) << " ";
                image << static_cast<unsigned>( sketches[ pixel_init + 2 ] ) << " ";
            }
            image << "\n";
        }

        image.close();
    }
    else
    {
        std::cout << "ERROR: EXTENSION NOT COMPATIBLE" << std::endl;
    }    
}

void Film::paint_pixel(const Point &point, const Color &color)
{
    auto pixel_init(point.y() * (width * 3) + (point.x() * 3));
    pixels[pixel_init] = color.r();
    pixels[pixel_init + 1] = color.g();
    pixels[pixel_init + 2] = color.b();
}