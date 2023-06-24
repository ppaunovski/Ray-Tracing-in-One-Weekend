//
// Created by pauno on 6/22/2023.
//

#ifndef RAY_TRACING_IN_C___MATERIAL_H
#define RAY_TRACING_IN_C___MATERIAL_H

#include "constants.h"
#include "hittable.h"

//struct hit_record;

class material {
public:
    virtual bool scatter(const ray& ray_in, const hit_record& record, color& attenuation, ray& scattered) const = 0;
    virtual ~material()= default;
};


class lambertian : public material {
public:
    color albedo;
public:
    lambertian(const color& albedo) : albedo(albedo){}

    virtual bool scatter(const ray& ray_in, const hit_record& record, color& attenuation, ray& scattered) const override{
        auto scatter_direction = record.normal + random_unit_vector();

        if (scatter_direction.near_zero())
            scatter_direction = record.normal;

        scattered = ray(record.point, scatter_direction);
        attenuation = albedo;

        return true;
    }
};


class metal : public material{
public:
    color albedo;
    double fuzz;
public:
    metal(const color& albedo, const double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    virtual bool scatter(const ray& ray_in, const hit_record& record, color& attenuation, ray& scattered) const override{
        vec3 reflected = reflect(unit_vector(ray_in.direction()), record.normal);
        scattered = ray(record.point, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        // If the scattered ray and the normal point in the same direction
        // then return true, else return false
        return (dot(scattered.direction(), record.normal) > 0);
    }
};


class dielectric : public material{
public:
    double index_of_refraction;
public:
    dielectric(double index_of_refraction) : index_of_refraction(index_of_refraction){}

    virtual bool scatter (const ray& ray_in, const hit_record& record, color& attenuation, ray& scattered) const override{
        attenuation = color (1.0, 1.0, 1.0);
        double refraction_ratio = record.front_face ? (1.0/index_of_refraction) : index_of_refraction;

        vec3 unit_direction = unit_vector(ray_in.direction());
        vec3 refracted = refract(unit_direction, record.normal, refraction_ratio);

        scattered = ray(record.point, refracted);

        return true;
    }
};

#endif //RAY_TRACING_IN_C___MATERIAL_H
