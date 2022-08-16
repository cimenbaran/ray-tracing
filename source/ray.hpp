#ifndef RAY_H
#define RAY_H
#include <glm/vec3.hpp>

using glm::vec3;

class material;


struct Ray
{
    vec3 orig;
    vec3 dir;

	Ray() {};
    Ray(vec3 origin, vec3 direction):
    orig(origin), dir(direction){}

    vec3 at(float t)
    {
        return orig + t * dir;
    };
};

struct hitInfo {
    vec3 n;
    vec3 p;
    float t;
	bool front_face;
	std::shared_ptr<material> mat_ptr;


	inline void set_face_normal(const Ray& r, const vec3& outward_normal) {
		front_face = glm::dot(r.dir, outward_normal) < 0;
		n = front_face ? outward_normal : -outward_normal;
	}
};

#endif