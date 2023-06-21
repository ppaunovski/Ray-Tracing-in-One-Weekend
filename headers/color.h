//
// Created by pauno on 5/2/2023.
//

#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"
#include <fstream>

void write_color(std::ofstream &out, color pixel_color, int samples_per_pixel){
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    auto scale = 1.0 / samples_per_pixel;

    r *= scale;
    b *= scale;
    g *= scale;

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << " "
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << " "
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << "\n";
}

#endif
