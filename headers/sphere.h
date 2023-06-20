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
    sphere(point3 cen, double r) : center(cen), radius(r){};

    virtual bool hit (const ray& r, double t_min, double t_max, hit_record& rec) const override;

private:
    point3 center;
    double radius;
};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    vec3 oc = r.origin() - center;
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
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

    rec.t = root;
    rec.p = r.at(rec.t);
    rec.normal = (rec.p - center) / radius;

    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}
#endif //RAY_TRACING_IN_C___SPHERE_H
