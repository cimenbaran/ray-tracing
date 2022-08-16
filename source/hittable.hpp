#ifndef HITTABLE_H
#define HITTABLE_H
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "ray.hpp"
#include <vector>
#include "aabb.h"
class hittable
{
public:
    virtual bool hit(Ray r, double t_min, double t_max, hitInfo &info) { return false; };
	virtual bool bounding_box(float time0, float time1, aabb& output_box) const = 0;


    friend class HittableList;
};

class HittableList
{
public:
    std::vector<shared_ptr<hittable>> objects;

    HittableList() {}
    void add(shared_ptr<hittable> object);
	virtual bool bounding_box(float time0, float time1, aabb& output_box) const;
    bool hit(Ray r, double t_min, double t_max, hitInfo &rec);
};

void HittableList::add(shared_ptr<hittable> object)
{
    objects.push_back(object);
}

bool HittableList::hit(Ray r, double t_min, double t_max, hitInfo& rec) {
    hitInfo tempRec;
	float minDistance = t_max;
    bool hit_anything = false;

    for (const auto& object : objects) {
        if (object -> hit(r, t_min, minDistance, tempRec)) {
            hit_anything = true;
            const float distance = glm::distance(tempRec.p, r.orig);
            if(distance < minDistance) {
                minDistance = distance;
                rec = tempRec;
            }
        }
    }

    return hit_anything;
}

bool HittableList::bounding_box(float time0, float time1, aabb& output_box) const {
	if (objects.empty()) return false;

	aabb temp_box;
	bool first_box = true;

	for (const auto& object : objects) {
		if (!object->bounding_box(time0, time1, temp_box)) return false;
		output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
		first_box = false;
	}

	return true;
}

#endif