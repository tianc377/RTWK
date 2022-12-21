#include <iostream>

#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"


// #define STB_IMAGE_IMPLEMENTATION
// #include "stb-master/stb_image.h"
// #define STB_IMAGE_WRITE_IMPLEMENTATION
// #include "stb-master/stb_image_write.h"





// double hit_sphere(const point3& center, double radius, const ray& r) {
//     auto oc = r.origin() - center;
//     //(r - center)*(r - center) - radius * radius = 0;
//     auto a = r.direction().length_squared();//dot(r.direction(),r.direction());
//     auto half_b = dot((oc),r.direction()); //2.0 * dot((oc),r.direction());
//     auto c = oc.length_squared() - radius * radius; //dot(oc, oc) - radius * radius;
//     auto discriminant = half_b * half_b - a * c;
//     if (discriminant <0){
//         return -1.0;
//     }
//     else{
//         return (-half_b - sqrt(discriminant)) / a; 
//     }
// }


color ray_color(const ray& r, const hittable& world) {
    hit_record rec;
    if (world.hit(r, 0, infinity, rec)){
        return 0.5 * color(rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t)* color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() 
{
    
    constexpr int data_size = image_width*image_height*3;
    unsigned char data[data_size];

    //world
    hittable_list world;
    world.add(make_shared<sphere>(point3(0,0,-1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));


    //camera
    camera cam;

    // Render

    std::cerr << "P3\n" << image_width << ' ' << image_height << "\n255\n";


    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines_remaining:" << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            color pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                ray r= cam.get_ray(u, v);
                pixel_color += ray_color(r, world);

            }

            // color pixel_color(r, g, b);
            write_color(std::cout, pixel_color, data);
            
            // data[index++] = static_cast<int>(256 * clamp(pixel_color.x()/ samples_per_pixel, 0.0, 0.999));
            // data[index++] = static_cast<int>( 256 * clamp(pixel_color.y()/ samples_per_pixel, 0.0, 0.999));
            // data[index++] = static_cast<int>( 256 * clamp(pixel_color.z()/ samples_per_pixel, 0.0, 0.999));
            
            
            

            //std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    std::cerr << "\nDone.\n";
    stbi_write_png("antialise_sphere2.png", image_width, image_height, 3, data, image_width*3);

}