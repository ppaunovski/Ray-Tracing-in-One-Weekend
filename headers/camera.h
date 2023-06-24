//
// Created by pauno on 6/21/2023.
//

#ifndef RAY_TRACING_IN_C___CAMERA_H
#define RAY_TRACING_IN_C___CAMERA_H

#include "constants.h"

class camera{
private:
    point3 origin;
    point3 lower_left_corner;
    vec3 horizontal;
    vec3 vertical;
    vec3 u, v, w;
    double lens_radius;
public:
    camera(point3 look_from, point3 look_at, vec3 view_up, double vertical_fov, double aspect_ratio, double aperture, double focus_distance) {
        auto theta = degrees_to_radians(vertical_fov);
        auto h = tan(theta/2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = unit_vector(look_from - look_at);
        u = unit_vector(cross(view_up, w));
        v = cross(w, u);

        origin = look_from;

        horizontal = focus_distance * viewport_width * u;
        vertical = focus_distance * viewport_height * v;
        lower_left_corner = origin - horizontal/2 - vertical/2 - focus_distance * w;

        lens_radius = aperture / 2.0;
    }

    ray get_ray(double s, double t) const {
        vec3 rd = lens_radius * random_in_unit_disk();
        vec3 offset = u * rd.x() + v * rd.y();

        return ray(origin + offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
    }
};

#endif //RAY_TRACING_IN_C___CAMERA_H
