#ifndef BOX_HPP
#define BOX_HPP

#include "ray.hpp"

#include "aarect.h"
#include "hittable.hpp"

class box : public hittable {
public:
	box() {};
	box(const vec3& p0, const vec3& p1, shared_ptr<material> ptr);

	virtual bool hit(Ray r, double t_min, double t_max, hitInfo& info) override;

	virtual bool bounding_box(float time0, float time1, aabb& output_box) const override {
		output_box = aabb(box_min, box_max);
		return true;
	}

public:
	vec3 box_min;
	vec3 box_max;
	HittableList sides;
};

box::box(const vec3& p0, const vec3& p1, shared_ptr<material> ptr) {
	box_min = p0;
	box_max = p1;

	sides.add(make_shared<xy_rect>(p0.x, p1.x, p0.y, p1.y, p1.z, ptr));
	sides.add(make_shared<xy_rect>(p0.x, p1.x, p0.y, p1.y, p0.z, ptr));

	sides.add(make_shared<xz_rect>(p0.x, p1.x, p0.z, p1.z, p1.y, ptr));
	sides.add(make_shared<xz_rect>(p0.x, p1.x, p0.z, p1.z, p0.y, ptr));

	sides.add(make_shared<yz_rect>(p0.y, p1.y, p0.z, p1.z, p1.x, ptr));
	sides.add(make_shared<yz_rect>(p0.y, p1.y, p0.z, p1.z, p0.x, ptr));
}

bool box::hit(Ray r, double t_min, double t_max, hitInfo& info)  {
	return sides.hit(r, t_min, t_max, info);
}



#endif