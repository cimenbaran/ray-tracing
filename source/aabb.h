#ifndef AABB_H
#define AABB_H

#include "ray.hpp"

class aabb {
public:
	aabb() {}
	aabb(const vec3& a, const vec3& b) { minimum = a; maximum = b; }

	vec3 min() const { return minimum; }
	vec3 max() const { return maximum; }
	bool hit(const Ray& r, float t_min, float t_max) const;
	/*
	bool hit(const Ray& r, float t_min, float t_max) const {
		for (int a = 0; a < 3; a++) {
			float amin = (a == 0 ? minimum.x : (a == 1 ? minimum.y : minimum.z));
			float amax = (a == 0 ? minimum.x : (a == 1 ? minimum.y : minimum.z));
			float bb = (a == 0 ? r.orig.x : (a == 1 ? r.orig.y : r.orig.z));
			float cc = (a == 0 ? r.dir.x : (a == 1 ? r.dir.y : r.dir.z));

			float t0 = fmin((amin - bb) / cc,
				(amax - bb) / cc);
			float t1 = fmax((amin - cc) / cc,
				(amax - bb) / cc);
			t_min = fmax(t0, t_min);
			t_max = fmin(t1, t_max);
			if (t_max <= t_min)
				return false;
		}
		return true;
	}
	*/

	vec3 minimum;
	vec3 maximum;
};


inline bool aabb::hit(const Ray& r, float t_min, float t_max) const {
	for (int a = 0; a < 3; a++) {
		float amin = (a == 0 ? minimum.x : (a == 1 ? minimum.y : minimum.z));
		float amax = (a == 0 ? minimum.x : (a == 1 ? minimum.y : minimum.z));
		float bb = (a == 0 ? r.orig.x : (a == 1 ? r.orig.y : r.orig.z));
		float cc = (a == 0 ? r.dir.x : (a == 1 ? r.dir.y : r.dir.z));


		auto invD = 1.0f / cc;
		auto t0 = (amin - bb) * invD;
		auto t1 = (amax - bb) * invD;
		if (invD < 0.0f)
			std::swap(t0, t1);
		t_min = t0 > t_min ? t0 : t_min;
		t_max = t1 < t_max ? t1 : t_max;
		if (t_max <= t_min)
			return false;
	}
	return true;
}

aabb surrounding_box(aabb box0, aabb box1) {
	vec3 small(fmin(box0.min().x, box1.min().x),
		fmin(box0.min().y, box1.min().y),
		fmin(box0.min().z, box1.min().z));

	vec3 big(fmax(box0.max().x, box1.max().x),
		fmax(box0.max().y, box1.max().y),
		fmax(box0.max().z, box1.max().z));

	return aabb(small, big);
}
#endif