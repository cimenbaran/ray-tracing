#ifndef SPHERE_H
#define SPHERE_H
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "hittable.hpp"
#include "ray.hpp"
#include "material.hpp"

using glm::vec3;

class sphere : public hittable
{
public:
    vec3 center;
    float radius;
	shared_ptr<material> mat_ptr;

    sphere(vec3 cen, double r, shared_ptr<material> m) : center(cen), radius(r), mat_ptr(m) {};
    virtual bool hit(Ray ray, double t_min, double t_max, hitInfo &info) override;
	virtual bool bounding_box(float time0, float time1, aabb& output_box) const override;

};

bool sphere::hit(Ray ray, double t_min, double t_max, hitInfo& info) {
    
    vec3 w = ray.orig - center;
    float a = glm::dot(ray.dir, ray.dir);
    float b = 2.0f * glm::dot(ray.dir, w);
    float c = glm::dot(w,w) - radius*radius;

    float discriminant = b*b - 4*a*c;

    if(discriminant <= 0) {
        return false;
    }

	const float sqrt_discriminant = sqrt(discriminant);
    float t = (-b - sqrt_discriminant) / (2.0 * a);
	if (t < t_min || t_max < t) {
		t = (-b + sqrt_discriminant) / (2.0 * a);
		if (t < t_min || t_max < t) {
			return false;
		}
	}
    info.p = ray.at(t);
    info.n = info.p - center;
    info.t = t;
	info.mat_ptr = mat_ptr;
	vec3 outward_normal = (info.p - center) / radius;
	info.set_face_normal(ray, outward_normal);

    return t > 0;
}


bool sphere::bounding_box(float time0, float time1, aabb& output_box) const {
	output_box = aabb(
		center - vec3(radius, radius, radius),
		center + vec3(radius, radius, radius));
	return true;
}

#endif