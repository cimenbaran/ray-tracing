#ifndef CAMERA_H
#define CAMERA_H

#include "ray.hpp"
#include "utility.hpp"

using glm::vec3;


class camera {
public:
	camera(
		vec3   lookfrom,
		vec3   lookat,
		vec3   vup,
		float vfov, // vertical field-of-view in degrees
		float aspect_ratio
	) {
		float theta = degrees_to_radians(vfov);
		float h = tan(theta / 2);
		float viewport_height = 2.0 * h;
		float viewport_width = aspect_ratio * viewport_height;

		vec3 w = unit_vector(lookfrom - lookat);
		vec3 u = unit_vector(cross(vup, w));
		vec3 v = cross(w, u);

		origin = lookfrom;
		horizontal = viewport_width * u;
		vertical = viewport_height * v;
		lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - w;
	}

	Ray get_ray(float s, float t) const {
		return Ray(origin, lower_left_corner + s * horizontal + t * vertical - origin);
	}

private:
	vec3 origin;
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
};

#endif