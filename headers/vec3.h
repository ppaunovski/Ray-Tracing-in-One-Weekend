//
// Created by pauno on 5/2/2023.
//

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>
#include <fstream>

using std::sqrt;

class vec3{
public:
    double e[3];
public:
    vec3() : e{0,0,0} {}
    vec3(double e0, double e1, double e2) : e{e0,e1,e2} {}

    double x() const {return e[0];}
    double y() const {return e[1];}
    double z() const {return e[2];}

    bool near_zero() const{
        const auto s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

    inline static vec3 random(){
        return vec3(random_double(), random_double(), random_double());
    }

    inline static vec3 random(double min, double max){
        return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
    }

    vec3 operator-()const {
        return {-e[0], -e[1], -e[2]};
    }

    // read the i-th element in vec3
    double operator [] (int i) const {
        return e[i];
    }

    // get the reference of i-th element in vec3 - for writing
    double& operator [] (int i) {
        return e[i];
    }

    vec3& operator+=(const vec3 &v){
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];

        return *this;
    }

    vec3& operator *= (const double s){
        e[0] *= s;
        e[1] *= s;
        e[2] *= s;

        return *this;
    }

    vec3& operator /= (const double s){
        return *this *= 1/s;
    }

    double length_squared() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    double length() const {
        return sqrt(length_squared());
    }
};

// Utility functions

inline std::ostream& operator<<(std::ostream &out, const vec3 &v){
    return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

inline vec3 operator + (const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator - (const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator * (const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator * (const double s, const vec3 &v){
    return vec3(s*v.e[0], s*v.e[1], s*v.e[2]);
}

inline vec3 operator * (const vec3 &v, const double s){
    return s * v;
}

inline vec3 operator / (const vec3 &v, const double s){
    return 1/s * v;
}

inline double dot(const vec3 &v1, const vec3 &v2){
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2){
    return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

inline vec3 unit_vector(vec3 v){
    return v / v.length();
}

vec3 random_in_unit_sphere() {
    while (true) {
        auto p = vec3::random(-1,1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

vec3 random_in_hemisphere(const vec3& normal) {
    vec3 in_unit_sphere = random_in_unit_sphere();
    if (dot(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return -in_unit_sphere;
}

vec3 reflect(const vec3& vector, const vec3& normal){
    return vector - 2*dot(vector, normal) * normal;
}

vec3 refract (const vec3& uv, const vec3& n, double etai_over_etat){
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    vec3 r_out_perpendicular = etai_over_etat * (uv + cos_theta * n);
    vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perpendicular.length_squared())) * n;

    return r_out_perpendicular + r_out_parallel;
}

vec3 random_in_unit_disk() {
    while (true) {
        auto point = vec3(random_double(-1,1), random_double(-1,1), 0);
        if (point.length_squared() >= 1) continue;
        return point;
    }
}

// Aliases for vec3

using point3 = vec3;
using color = vec3;

#endif

