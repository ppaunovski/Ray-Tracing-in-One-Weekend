//
// Created by pauno on 5/2/2023.
//

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray {
public:
    point3 Origin;
    vec3 Direction;
public:
    ray(){}
    ray(const point3& origin, const vec3& direction){
        this->Origin = origin;
        this->Direction = direction;
    }

    point3 origin() const {return Origin;}

    vec3 direction() const {return Direction;}

    point3 at (double t) const {
        return Origin + t * Direction;
    }

};

#endif
