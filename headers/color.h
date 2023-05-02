//
// Created by pauno on 5/2/2023.
//

#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <fstream>

void write_color(std::ofstream &out, color pixel_color){
    out << static_cast<int>(255.999 * pixel_color.x()) << " "
        << static_cast<int>(255.999 * pixel_color.y()) << " "
        << static_cast<int>(255.999 * pixel_color.z()) << "\n";
}

#endif
