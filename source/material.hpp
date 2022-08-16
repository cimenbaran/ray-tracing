#ifndef MATERIAL_H
#define MATERIAL_H
#include <glm/vec3.hpp>
#include "ray.hpp"

using glm::vec3;

struct hitInfo;

class solid_color {
public:
	solid_color() {}
	solid_color(vec3 c) : color_value(c) {}

	solid_color(double red, double green, double blue)
		: solid_color(vec3(red, green, blue)) {}

	virtual vec3 value() const {
		return color_value;
	}

private:
	vec3 color_value;
};

class material {
public:
	virtual vec3 emitted() const {
		return vec3(0, 0, 0);
	}
	virtual bool scatter(
		const Ray& r_in, const hitInfo& rec, vec3& attenuation, Ray& scattered
	) const = 0;
};

class lambertian : public material {
public:
	lambertian(const vec3& a) : albedo(a) {}

	virtual bool scatter(
		const Ray& r_in, const hitInfo& info, vec3& attenuation, Ray& scattered
	) const override {
		auto scatter_direction = info.n + randomUnitVector();

		if (near_zero(scatter_direction)) {
			scatter_direction = info.n;
		}


		scattered = Ray(info.p, scatter_direction);
		attenuation = albedo;
		return true;
	}

public:
	vec3 albedo;
};

class metal : public material {
public:
	metal(const vec3& a) : albedo(a) {}

	virtual bool scatter(
		const Ray& r_in, const hitInfo& info, vec3& attenuation, Ray& scattered
	) const override {
		vec3 reflected = reflect(unit_vector(r_in.dir), info.n);
		scattered = Ray(info.p, reflected);
		attenuation = albedo;
		bool isTrue = (glm::dot(scattered.dir, info.n) > 0);
		if (isTrue) {
			return true;
		}
		return isTrue;
	}

public:
	vec3 albedo;
};

class dielectric : public material {
public:
	dielectric(float index_of_refraction) : ir(index_of_refraction) {}

	virtual bool scatter(
		const Ray& r_in, const hitInfo& info, vec3& attenuation, Ray& scattered
	) const override {
		attenuation = vec3(1.0, 1.0, 1.0);
		float refraction_ratio = info.front_face ? (1.0 / ir) : ir;

		vec3 unit_direction = unit_vector(r_in.dir);

		float cos_theta = fmin(glm::dot(-unit_direction, info.n), 1.0);
		float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

		bool cannot_refract = refraction_ratio * sin_theta > 1.0;
		vec3 direction;

		if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randFloat())
			direction = reflect(unit_direction, info.n);
		else
			direction = refract(unit_direction, info.n, refraction_ratio);

		scattered = Ray(info.p, direction);

		return true;
	}

public:
	float ir; // Index of Refraction


private:
	static float reflectance(float cosine, float ref_idx) {
		// Use Schlick's approximation for reflectance.
		auto r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0 * r0;
		return r0 + (1 - r0)*pow((1 - cosine), 5);
	}
};


class diffuse_light : public material {
public:
	diffuse_light(vec3 c) : emit(make_shared<solid_color>(c)) {}

	virtual bool scatter(
		const Ray& r_in, const hitInfo& rec, vec3& attenuation, Ray& scattered
	) const override {
		return false;
	}

	virtual vec3 emitted() const override {
		return emit->value();
	}

public:
	shared_ptr<solid_color> emit;
};
#endif