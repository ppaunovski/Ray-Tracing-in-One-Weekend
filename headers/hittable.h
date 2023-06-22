//
// Created by pauno on 6/20/2023.
//

#ifndef HITTABLE_H
#define HITTABLE_H

#include "constants.h"

class material;

struct hit_record{
    point3 point;
    vec3 normal;
    shared_ptr<material> material_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(const ray& r, const vec3& outward_normal){
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable{
public:
    virtual bool hit(const ray& ray, double t_min, double t_max, hit_record& record) const = 0;
};

#endif //HITTABLE_H
