//
// Created by pauno on 6/20/2023.
//

#ifndef RAY_TRACING_IN_C___SPHERE_H
#define RAY_TRACING_IN_C___SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable{
public:
    sphere(){}
    sphere(point3 cen, double radius, std::shared_ptr<material> material)
    : center(cen), radius(radius), material_ptr(material){};

    virtual bool hit (const ray& ray, double t_min, double t_max, hit_record& record) const override;

public:
    point3 center;
    double radius;
    std::shared_ptr<material> material_ptr;
};

bool sphere::hit(const ray& ray, double t_min, double t_max, hit_record& record) const {
    vec3 oc = ray.origin() - center;
    auto a = ray.direction().length_squared();
    auto half_b = dot(oc, ray.direction());
    auto c = oc.length_squared() - radius*radius;

    auto discriminant = half_b*half_b - a*c;

    if (discriminant < 0)
        return false;

    auto sqrtd = sqrt(discriminant);

    // Find nearest root in acceptable range

    auto root = (-half_b - sqrtd) / a;

    if (root < t_min || t_max < root){
        root = (-half_b + sqrtd) / a;

        if (root < t_min || root > t_max)
            return false;
    }

    record.t = root;
    record.point = ray.at(record.t);
    record.normal = (record.point - center) / radius;
    record.material_ptr = material_ptr;

    vec3 outward_normal = (record.point - center) / radius;
    record.set_face_normal(ray, outward_normal);

    return true;
}
#endif //RAY_TRACING_IN_C___SPHERE_H
