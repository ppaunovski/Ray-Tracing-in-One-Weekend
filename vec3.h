//
// Created by pauno on 5/2/2023.
//

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3{
public:
    vec3() : e{0,0,0} {}
    vec3(double e0, double e1, double e2) : e{e0,e1,e2} {}

    double x() const {return e[0];}
    double y() const {return e[1];}
    double z() const {return e[2];}

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

public:
    double e[3];
};

// Aliases for vec3

using point3 = vec3;
using color = vec3;

#endif
