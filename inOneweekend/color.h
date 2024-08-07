#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb-master/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb-master/stb_image_write.h"

// Image
constexpr auto aspect_ratio = 16.0/9.0;
constexpr int image_width = 256;
constexpr int image_height = 256;//static_cast<int>(image_width / aspect_ratio);
constexpr int samples_per_pixel = 128;

void write_color(std::ostream &out, color pixel_color, unsigned char* data, int& index) 
{    
    

    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples.
    auto scale = 1.0/ samples_per_pixel;
    r = sqrt(r *scale);
    g = sqrt(g *scale);
    b = sqrt(b *scale);

    data[index++] = static_cast<int>(256 * clamp(r, 0.0, 0.999999));
    data[index++] = static_cast<int>(256 * clamp(g, 0.0, 0.999999));
    data[index++] = static_cast<int>(256 * clamp(b, 0.0, 0.999999));

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999999)) << '\n';
    
    

    //stbi_write_png("antialise_sphere2.png", image_width, image_height, 3, data, image_width*3);

}

#endif