#ifndef AARECT_H
#define AARECT_H

#include "ray.hpp"
#include "utility.hpp"
#include "hittable.hpp"

class xy_rect : public hittable {
public:
	xy_rect() {}

	xy_rect(double _x0, double _x1, double _y0, double _y1, double _k,
		shared_ptr<material> mat)
		: x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(mat) {};

	virtual bool hit(Ray r, double t_min, double t_max, hitInfo& info) override;

	virtual bool bounding_box(float time0, float time1, aabb& output_box) const override {
		// The bounding box must have non-zero width in each dimension, so pad the Z
		// dimension a small amount.
		output_box = aabb(vec3(x0, y0, k - 0.0001), vec3(x1, y1, k + 0.0001));
		return true;
	}

public:
	shared_ptr<material> mp;
	double x0, x1, y0, y1, k;
};

bool xy_rect::hit(Ray r, double t_min, double t_max, hitInfo & info) {
	auto t = (k - r.orig.z) / r.dir.z;
	if (t < t_min || t > t_max)
		return false;
	auto x = r.orig.x + t * r.dir.x;
	auto y = r.orig.y + t * r.dir.y;
	if (x < x0 || x > x1 || y < y0 || y > y1)
		return false;
	//info.u = (x - x0) / (x1 - x0);
	//info.v = (y - y0) / (y1 - y0);
	info.t = t;
	auto outward_normal = vec3(0, 0, 1);
	info.set_face_normal(r, outward_normal);
	info.mat_ptr = mp;
	info.p = r.at(t);
	return true;
}

class xz_rect : public hittable {
public:
	xz_rect() {}

	xz_rect(double _x0, double _x1, double _z0, double _z1, double _k,
		shared_ptr<material> mat)
		: x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(mat) {};

	virtual bool hit(Ray r, double t_min, double t_max, hitInfo& info) override;

	virtual bool bounding_box(float time0, float time1, aabb& output_box) const override {
		// The bounding box must have non-zero width in each dimension, so pad the Y
		// dimension a small amount.
		output_box = aabb(vec3(x0, k - 0.0001, z0), vec3(x1, k + 0.0001, z1));
		return true;
	}

public:
	shared_ptr<material> mp;
	double x0, x1, z0, z1, k;
};

class yz_rect : public hittable {
public:
	yz_rect() {}

	yz_rect(double _y0, double _y1, double _z0, double _z1, double _k,
		shared_ptr<material> mat)
		: y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(mat) {};

	virtual bool hit(Ray r, double t_min, double t_max, hitInfo& info) override;

	virtual bool bounding_box(float time0, float time1, aabb& output_box) const override {
		// The bounding box must have non-zero width in each dimension, so pad the X
		// dimension a small amount.
		output_box = aabb(vec3(k - 0.0001, y0, z0), vec3(k + 0.0001, y1, z1));
		return true;
	}

public:
	shared_ptr<material> mp;
	double y0, y1, z0, z1, k;
};

bool xz_rect::hit(Ray r, double t_min, double t_max, hitInfo& info) {
	auto t = (k - r.orig.y) / r.dir.y;
	if (t < t_min || t > t_max)
		return false;
	auto x = r.orig.x + t * r.dir.x;
	auto z = r.orig.z + t * r.dir.z;
	if (x < x0 || x > x1 || z < z0 || z > z1)
		return false;
	//info.u = (x - x0) / (x1 - x0);
	//info.v = (z - z0) / (z1 - z0);
	info.t = t;
	auto outward_normal = vec3(0, 1, 0);
	info.set_face_normal(r, outward_normal);
	info.mat_ptr = mp;
	info.p = r.at(t);
	return true;
}

bool yz_rect::hit(Ray r, double t_min, double t_max, hitInfo& info) {
	auto t = (k - r.orig.x) / r.dir.x;
	if (t < t_min || t > t_max)
		return false;
	auto y = r.orig.y + t * r.dir.y;
	auto z = r.orig.z + t * r.dir.z;
	if (y < y0 || y > y1 || z < z0 || z > z1)
		return false;
	//info.u = (y - y0) / (y1 - y0);
	//info.v = (z - z0) / (z1 - z0);
	info.t = t;
	auto outward_normal = vec3(1, 0, 0);
	info.set_face_normal(r, outward_normal);
	info.mat_ptr = mp;
	info.p = r.at(t);
	return true;
}

#endif