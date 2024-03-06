#include <iostream>

#include "rtweekend.h"

#include "color.h"
#include "hittable_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"



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


color ray_color(const ray& r, const hittable& world, int depth) {
    hit_record rec;

    if (depth <= 0)
        return color(0,0,0);

    if (world.hit(r, 0.001, infinity, rec)){
        ray scattered;
        color attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_color(scattered, world, depth -1);
        return color(0,0,0);

        // point3 target = rec.p + random_in_hemisphere(rec.normal); //rec.normal + random_unit_vector();
        // return 0.5 * ray_color(ray(rec.p, target - rec.p), world, depth-1);  //return 0.5 * color(rec.normal + color(1,1,1));
    }
    vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t)* color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() 
{
    
    constexpr int data_size = image_width*image_height*3;
    unsigned char data[data_size];
    int index = 0;
    const int max_depth = 50;

    //world

    hittable_list world;

    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
    auto material_left   = make_shared<metal>(color(0.8, 0.8, 0.8), 0.3);
    auto material_right  = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0,    0.0, -1.0),   0.5, material_center));   //material pointer was added in sphere.h
    world.add(make_shared<sphere>(point3(-1.0,   0.0, -1.0),   0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0,    0.0, -1.0),   0.5, material_right));



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
                pixel_color += ray_color(r, world, max_depth);

            }

            write_color(std::cout, pixel_color, data, index);
            

        }
    }
    std::cerr << "\nDone.\n";
    stbi_write_png("dielectric_material_fuzz.png", image_width, image_height, 3, data, image_width*3);

}