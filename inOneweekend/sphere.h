#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
    public:
        sphere() {}
        sphere(point3 cen, double r) : center(cen), radius(r) {};

        virtual bool hit(
            const ray& r, double t_min, double t_max, hit_record& rec) const override;

    public:
        point3 center;
        double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const{
    auto oc = r.origin() - center;
    //(r - center)*(r - center) - radius * radius = 0;
    auto a = r.direction().length_squared();//dot(r.direction(),r.direction());
    auto half_b = dot(oc,r.direction()); //2.0 * dot((oc),r.direction());
    auto c = oc.length_squared() - radius * radius; //dot(oc, oc) - radius * radius;
    
    auto discriminant = half_b * half_b - a * c;
    if (discriminant <0) return false;
    auto sqrtd = sqrt(discriminant);

    auto root =  (-half_b - sqrtd) / a;    // - sqrtd （-b - sqrt(b2 - 4ac)) 是更近的交点，先找近的
    if (root < t_min || t_max < root) {        
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root) 
            return false;
    }

    rec.t = root;
    rec.p = r.at(rec.t);
    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}


#endif