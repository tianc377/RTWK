#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb-master/stb_image.h"
// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "stb-master/stb_image_write.h"

void write_color(std::ostream &out, color pixel_color, int samples_per_pixel, int image_width, int image_height) {
    
    constexpr int data_size = 360000;//image_width*image_height*3;
    unsigned char data[data_size];
    //std::vector<char> data(image_width*image_height*3);
    int index = 0;

    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples.
    auto scale = 1.0/ samples_per_pixel;
    r *= scale;
    g *= scale;
    b *= scale;


    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
    
    // data[index++] = static_cast<int>(256 * clamp(r, 0.0, 0.999));
    // data[index++] = static_cast<int>(256 * clamp(g, 0.0, 0.999));
    // data[index++] = static_cast<int>(256 * clamp(b, 0.0, 0.999));

    // stbi_write_png("antialise_sphere.png", image_width, image_height, 3, data, image_width*3);

}

#endif