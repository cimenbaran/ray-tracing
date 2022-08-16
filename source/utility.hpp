#ifndef UTILITY_H
#define UTILITY_H
#define _USE_MATH_DEFINES
#include <glm/vec3.hpp>
#include <fstream>
#include <vector>
#include "ray.hpp"
#include <limits>
#include <algorithm>
#include <math.h> // for pi



using namespace std;
using glm::vec3;
void writeImage(vec3 color, std::ofstream& output)
{
    int r = min(sqrt(color.r) * 255.0f, 255.0f);
    int g = min(sqrt(color.g) * 255.0f, 255.0f);
    int b = min(sqrt(color.b) * 255.0f, 255.0f);

    output << r << " " << g << " " << b << endl;
}

float randFloat() {
    return 2.0 * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) - 1;
}

float randFloat(float min, float max) {
	return min + (max - min)*randFloat();
}

float Q_rsqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long *)&y;                       // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);               // what the fuck? 
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));   // 1st iteration

	return y;
}

vec3 randomUnitVector() {
	return vec3(randFloat(), randFloat(), randFloat());
}

bool near_zero(vec3 vec) {
	// Return true if the vector is close to zero in all dimensions.
	const auto s = 1e-8;
	return (fabs(vec.x) < s) && (fabs(vec.y) < s) && (fabs(vec.z) < s);
}

vec3 reflect(const vec3& v, const vec3& n) {
	return  v - 2 * glm::dot(v, n)*n;
}

float length_squared(const vec3 & v) {
	return v.x*v.x + v.y*v.y + v.z*v.z;
}

vec3 unit_vector(vec3 v) {
	float t = Q_rsqrt(length_squared(v));
	return  v * t; // vec3(t *v.x, t *v.y, t *v.z);
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
	return vec3(u.y * v.z - u.z * v.y,
		u.z * v.x - u.x * v.z,
		u.x * v.y - u.y * v.x);
}

vec3 refract(const vec3& uv, const vec3& n, float etai_over_etat) {
	float cos_theta = fmin(glm::dot(-uv, n), 1.0);
	vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	vec3 r_out_parallel = float(-sqrt(fabs(1.0 - length_squared(r_out_perp)))) * n;
	return r_out_perp + r_out_parallel;
}

inline double degrees_to_radians(double degrees) {
	return degrees * M_PI / 180.0;
}
inline static vec3 random_vector() {
	return vec3(randFloat(), randFloat(), randFloat());
}

inline static vec3 random_vector(double min, double max) {
	return vec3(randFloat(min, max), randFloat(min, max), randFloat(min, max));
}

inline int random_int(int min, int max) {
	// Returns a random integer in [min,max].
	return static_cast<int>(randFloat(min, max + 1));
}

#endif