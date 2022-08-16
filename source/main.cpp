#include <iostream>
#include <fstream>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include "utility.hpp"
#include "sphere.hpp"
#include "material.hpp"
#include "camera.hpp"
#include "aarect.h"
#include "box.hpp"
using namespace std;
using glm::vec3;

HittableList random_scene() {
	HittableList scene;

	auto ground_material = make_shared<diffuse_light>(vec3(4, 0.5, 0.5));
	scene.add(make_shared<sphere>(vec3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float choose_mat = randFloat();
			vec3 center(a + 0.9*randFloat(), 0.2, b + 0.9*randFloat());

			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.75) {
					// diffuse
					vec3 albedo = random_vector() * random_vector();
					sphere_material = make_shared<lambertian>(albedo);
					scene.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.9) {
					// metal
					vec3 albedo = random_vector(0.5, 1);
					sphere_material = make_shared<metal>(albedo);
					scene.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					sphere_material = make_shared<dielectric>(1.5);
					scene.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<diffuse_light>(vec3(randFloat(0, 4), randFloat(0, 4), randFloat(0, 4)));
					scene.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	scene.add(make_shared<sphere>(vec3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(vec3(0.4, 0.2, 0.1));
	scene.add(make_shared<sphere>(vec3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(vec3(0.7, 0.6, 0.5));
	scene.add(make_shared<sphere>(vec3(4, 1, 0), 1.0, material3));

	return scene;
}


HittableList just_a_scene() {
	HittableList scene;
	auto material_ground = make_shared<lambertian>(vec3(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(vec3(0.7, 0.3, 0.3));
	auto material_left = make_shared<metal>(vec3(0.8, 0.8, 0.8));
	//auto material_right = make_shared<metal>(vec3(0.8, 0.6, 0.2));
	auto material_right = make_shared<dielectric>(1.5);

	scene.add(make_shared<sphere>(vec3(0.0, -100.5, -1.0), 100.0, material_ground));
	scene.add(make_shared<sphere>(vec3(0.0, 0.0, -1.0), 0.5, material_center));
	scene.add(make_shared<sphere>(vec3(-1.0, 0.0, -1.0), 0.5, material_left));
	scene.add(make_shared<sphere>(vec3(1.0, 0.0, -1.0), 0.5, material_right));
	scene.add(make_shared<sphere>(vec3(1.0, 0.0, -1.0), -0.45, material_right));
	return scene;
}

HittableList task_1() {
	HittableList scene;

	auto material_ground = make_shared<lambertian>(vec3(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(vec3(0.7, 0.3, 0.3));
	auto material_left = make_shared<lambertian>(vec3(0.3, 0.3, 0.3));
	auto material_right = make_shared<lambertian>(vec3(0.5, 0.6, 0.7));
	auto material_little_r = make_shared<lambertian>(vec3(0.2, 0.5, 0.8));
	auto material_little_l = make_shared<lambertian>(vec3(0.1, 0.4, 0.9));


	scene.add(make_shared<sphere>(vec3(0.0, -100.5, -1.0), 100.0, material_ground));
	scene.add(make_shared<sphere>(vec3(0.0, 0.0, -1.0), 0.5, material_center));
	scene.add(make_shared<sphere>(vec3(-1.0, 0.0, -1.0), 0.5, material_left));
	scene.add(make_shared<sphere>(vec3(1.0, 0.0, -1.0), 0.5, material_right));
	scene.add(make_shared<sphere>(vec3(0.3, -0.35, -0.3), 0.15, material_little_l));
	scene.add(make_shared<sphere>(vec3(-0.8, -0.3, -0.3), 0.2, material_little_r));
	return scene;

}
HittableList task_4() {
	HittableList scene;
	auto material_ground = make_shared<lambertian>(vec3(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(vec3(0.7, 0.3, 0.3));
	auto material_left = make_shared<metal>(vec3(0.8, 0.8, 0.8));
	auto material_right = make_shared<metal>(vec3(0.8, 0.6, 0.2));
	auto material_little = make_shared<lambertian>(vec3(0.6, 0.3, 0.7));


	scene.add(make_shared<sphere>(vec3(0.0, -100.5, -1.0), 100.0, material_ground));
	scene.add(make_shared<sphere>(vec3(0.0, 0.0, -1.0), 0.5, material_center));
	scene.add(make_shared<sphere>(vec3(-1.0, 0.0, -1.0), 0.5, material_left));
	scene.add(make_shared<sphere>(vec3(1.0, 0.0, -1.0), 0.5, material_right));
	scene.add(make_shared<sphere>(vec3(0.2, -0.3, -0.3), 0.2, material_little));

	return scene;
}

HittableList task_5() {
	HittableList scene;
	auto material_ground = make_shared<lambertian>(vec3(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(vec3(0.7, 0.3, 0.3));
	auto material_left = make_shared<dielectric>(1.333f); // water
	auto material_right = make_shared<lambertian>(vec3(0.8, 0.6, 0.2));
	auto material_little = make_shared<dielectric>(2.417f); // diamond


	scene.add(make_shared<sphere>(vec3(0.0, -100.5, -1.0), 100.0, material_ground));
	scene.add(make_shared<sphere>(vec3(-0.5, 0.0, -1.0), 0.5, material_center));
	scene.add(make_shared<sphere>(vec3(-1.0, 0.0, 0), 0.5, material_left));
	scene.add(make_shared<sphere>(vec3(1.0, 0.0, -1.0), 0.5, material_right));
	scene.add(make_shared<sphere>(vec3(0.2, -0.3, -0.3), 0.2, material_little));

	return scene;
}

HittableList task_6() {
	HittableList scene;
	scene.add(make_shared<sphere>(vec3(0, -1000, 0), 1000, make_shared<lambertian>(vec3(0.8, 0.3, 0.5))));
	scene.add(make_shared<sphere>(vec3(0, 2, -6), 2, make_shared<lambertian>(vec3(0.7, 0.3, 0.3)))); //middle
	scene.add(make_shared<sphere>(vec3(-5, 2, 0), 2, make_shared<lambertian>(vec3(0.3, 0.7, 0.3)))); // left
	scene.add(make_shared<sphere>(vec3(5, 2, 0), 2, make_shared<lambertian>(vec3(0.7, 0.3, 0.7)))); // right
	scene.add(make_shared<sphere>(vec3(-4, 2, -10), 2, make_shared<metal>(vec3(0.8, 0.8, 0.8)))); // left back
	scene.add(make_shared<sphere>(vec3(4, 2, -10), 2, make_shared<metal>(vec3(0.7, 0.3, 0.7)))); // right back
	scene.add(make_shared<sphere>(vec3(-8, 2, 5), 2, make_shared<metal>(vec3(0.7, 0.7, 0.3)))); // left front
	scene.add(make_shared<sphere>(vec3(8, 2, 5), 2, make_shared<metal>(vec3(0.3, 0.7, 0.7)))); // right front



	auto difflight_red = make_shared<diffuse_light>(vec3(4, 0.5, 0.5));
	auto difflight_blue = make_shared<diffuse_light>(vec3(0.5, 0.5, 4));
	auto difflight_green = make_shared<diffuse_light>(vec3(0.5, 4, 0.5));


	scene.add(make_shared<xy_rect>(-2, 2, -2, 2, 5, difflight_red));
	scene.add(make_shared<sphere>(vec3(-3, 9, -8), 2, difflight_blue));
	scene.add(make_shared<sphere>(vec3(3, 9, -8), 2, difflight_green));



	return scene;
}

HittableList task_6_2() {
	HittableList scene;
	scene.add(make_shared<sphere>(vec3(0, -1000, 0), 1000, make_shared<lambertian>(vec3(0.8, 0.3, 0.5))));
	scene.add(make_shared<sphere>(vec3(0, 2, -6), 2, make_shared<lambertian>(vec3(0.7, 0.3, 0.3)))); //middle
	scene.add(make_shared<sphere>(vec3(-3, 2, 0), 2, make_shared<lambertian>(vec3(0.3, 0.7, 0.3)))); // left
	scene.add(make_shared<sphere>(vec3(2, 2, 0), 2, make_shared<lambertian>(vec3(0.7, 0.3, 0.7)))); // right
	scene.add(make_shared<sphere>(vec3(-8, 2, -10), 2, make_shared<metal>(vec3(0.8, 0.8, 0.8)))); // left back
	scene.add(make_shared<sphere>(vec3(1, 2, -10), 2, make_shared<metal>(vec3(0.7, 0.3, 0.7)))); // right back
	scene.add(make_shared<sphere>(vec3(-4, 2, 5), 2, make_shared<metal>(vec3(0.7, 0.7, 0.3)))); // left front
	scene.add(make_shared<sphere>(vec3(7, 2, 5), 2, make_shared<metal>(vec3(0.3, 0.7, 0.7)))); // right front



	auto difflight_red = make_shared<diffuse_light>(vec3(4, 2, 1));
	auto difflight_blue = make_shared<diffuse_light>(vec3(2.5, 1.5, 4));
	auto difflight_green = make_shared<diffuse_light>(vec3(2, 4, 3));


	scene.add(make_shared<xy_rect>(-2, 2, -2, 2, 5, difflight_red));
	scene.add(make_shared<sphere>(vec3(-3, 9, -8), 2, difflight_blue));
	scene.add(make_shared<sphere>(vec3(3, 9, -8), 2, difflight_green));



	return scene;
}

HittableList task_7() {
	HittableList scene;
	scene.add(make_shared<sphere>(vec3(0, -1000, 0), 1000, make_shared<lambertian>(vec3(0.8, 0.3, 0.5))));
	scene.add(make_shared<sphere>(vec3(0, 2, -6), 2, make_shared<lambertian>(vec3(0.7, 0.3, 0.3)))); //middle
	scene.add(make_shared<box>(vec3(-7, 0, -2), vec3(-3, 4, 2), make_shared<lambertian>(vec3(0.3, 0.7, 0.3)))); // left
	scene.add(make_shared<sphere>(vec3(5, 2, 0), 2, make_shared<lambertian>(vec3(0.7, 0.3, 0.7)))); // right
	scene.add(make_shared<sphere>(vec3(-4, 2, -10), 2, make_shared<metal>(vec3(0.8, 0.8, 0.8)))); // left back
	scene.add(make_shared<sphere>(vec3(4, 2, -10), 2, make_shared<metal>(vec3(0.7, 0.3, 0.7)))); // right back
	scene.add(make_shared<sphere>(vec3(-8, 2, 5), 2, make_shared<metal>(vec3(0.7, 0.7, 0.3)))); // left front
	scene.add(make_shared<box>(vec3(6, 0, 3), vec3(10, 4, 7), make_shared<metal>(vec3(0.9, 0.7, 0.7)))); // right front


	auto difflight_red = make_shared<diffuse_light>(vec3(4, 0.5, 0.5));
	auto difflight_blue = make_shared<diffuse_light>(vec3(0.5, 0.5, 4));
	auto difflight_green = make_shared<diffuse_light>(vec3(0.5, 4, 0.5));


	scene.add(make_shared<box>(vec3(-2, 0, 5), vec3(2, 4, 9), difflight_red));
	scene.add(make_shared<sphere>(vec3(-3, 5, -13), 2.5, difflight_blue));
	scene.add(make_shared<sphere>(vec3(3, 5, -13), 2.5, difflight_green));



	return scene;
}

HittableList task_3() {
	HittableList scene;
	auto difflight_red = make_shared<diffuse_light>(vec3(4, 0.5, 0.5));

	scene.add(make_shared<sphere>(vec3(0, -1000, 0), 1000, make_shared<lambertian>(vec3(0.6, 0.6, 0.6))));
	scene.add(make_shared<box>(vec3(-7, 0, -2), vec3(-3, 4, 2), make_shared<lambertian>(vec3(0.3, 0.7, 0.3)))); // left
	scene.add(make_shared<box>(vec3(6, 0, 3), vec3(10, 4, 7), make_shared<metal>(vec3(0.9, 0.7, 0.7)))); // right front
	scene.add(make_shared<box>(vec3(-2, 0, 5), vec3(2, 4, 9), difflight_red));

	return scene;
}


HittableList simple_light() {
	HittableList objects;

	objects.add(make_shared<sphere>(vec3(0, -1000, 0), 1000, make_shared<lambertian>(vec3(0.8, 0.3, 0.5))));
	objects.add(make_shared<sphere>(vec3(0, 2, 0), 2, make_shared<lambertian>(vec3(0.7, 0.3, 0.3))));


	auto difflight = make_shared<diffuse_light>(vec3(4, 4, 4));
	objects.add(make_shared<xy_rect>(3, 5, 1, 3, -2, difflight));


	return objects;
}

vec3 rayColor(Ray & ray, const vec3 & background, HittableList& world, int depth) {
	if (depth <= 0) {
		return vec3(0);
	}

	hitInfo info;
	if (!world.hit(ray, 0.001, std::numeric_limits<float>::max(), info)) {
		return background;
	}

	Ray scattered;
	vec3 attenuation;
	vec3 emitted = info.mat_ptr->emitted();

	if (!info.mat_ptr->scatter(ray, info, attenuation, scattered)) {
		return emitted;
	}

	return emitted + attenuation * rayColor(scattered, background, world, depth - 1);
}

int main()
{
	// image
	const float aspectRatio = 16.0 / 9.0;
	const int imageWidth = 1920, imageHeight = imageWidth / aspectRatio;
	const int depth = 1000;
	int sample = 50;
	const float R = cos(M_PI / 4);

	vec3 background(0, 0, 0);
	// camera
	vec3 lookfrom(-2, 2, 1);
	vec3 lookat(0, 0, -1);
	vec3 vup(0, 1, 0);
	float vfov = 90.0f;
	//camera cam(vec3(-2, 2, 1), vec3(0, 0, -1), vec3(0, 1, 0), 90, aspectRatio);


	// scene
	HittableList scene;


	switch (10) {
	case 1:
		scene = just_a_scene();
		background = vec3(0.70, 0.80, 1.00);
		break;

	case 2:
		scene = simple_light();
		sample = 400;
		background = vec3(0, 0, 0);
		lookfrom = vec3(26, 3, 6);
		lookat = vec3(0, 2, 0);
		vfov = 20.0;
		break;

	case 3: // Task 2
		scene = just_a_scene();
		sample = 5; // 100
		background = vec3(0.70, 0.80, 1.00);
		lookfrom = vec3(0, 2, 3);
		lookat = vec3(0, 0, 0);
		vfov = 20.0;
		break;

	case 4: // Task 1
		scene = task_1();
		sample = 50;
		background = vec3(0.20, 0.40, 1.00);
		lookfrom = vec3(0, 0, 1);
		lookat = vec3(0, 0, -1);
		break;

	case 44: // Task 1_2
		scene = task_1();
		sample = 50;
		background = vec3(0.20, 0.40, 1.00);
		lookfrom = vec3(-6, 0, 1);
		lookat = vec3(0, 0, -1);
		break;

	case 6: // Task 4
		scene = task_4();
		background = vec3(0.40, 0.60, 1.00);
		lookfrom = vec3(0, 0, 1);
		lookat = vec3(0, 0, -1);
		break;

	case 7: // Task 5
		scene = task_5();
		background = vec3(0.40, 0.60, 1.00);
		lookfrom = vec3(0, 0, 1);
		lookat = vec3(0, 0, -1);
		break;

	case 8: // Task 6
		scene = task_6();
		sample = 200;
		background = vec3(0, 0, 0);
		lookfrom = vec3(0, 12, 20);
		lookat = vec3(0, 2, 0);
		vfov = 50.0;
		break;

	case 9: // Task 6_2
		scene = task_6_2();
		sample = 200;
		background = vec3(0.3, 0.5, 0.7);
		lookfrom = vec3(0, 12, 20);
		lookat = vec3(0, 2, 0);
		vfov = 50.0;
		break;

	case 10: // Task 7
		scene = task_7();
		sample = 200; // 200
		background = vec3(0, 0, 0);
		lookfrom = vec3(0, 12, 20);
		lookat = vec3(0, 2, 0);
		vfov = 50.0;
		break;
	case 11: // Task 3
		scene = task_3();
		sample = 100; // 200
		background = vec3(0, 0, 0);
		lookfrom = vec3(0, 12, 20);
		lookat = vec3(0, 2, 0);
		vfov = 50.0;
	default:
	case 5:
		background = vec3(0.0, 0.0, 0.0);
		break;
	}

	camera cam(lookfrom, lookat, vup, vfov, aspectRatio);


	// output
	ofstream output("output.ppm");
	output << "P3" << endl;
	output << imageWidth << " " << imageHeight << endl;
	output << 255 << endl;

	// render
	for (int y = imageHeight - 1; y >= 0; y--)
	{
		std::cerr << "\rScanlines remaining: " << y << ' ' << std::flush;
		for (int x = 0; x < imageWidth; x++)
		{
			if (x == 100 && y == 225) {
				int aaaaaaaa = 1;
			}
			vec3 vec3(0);
			for (int s = 0; s < sample; s++)
			{
				float u = ((x + randFloat()) / (imageWidth - 1.0));
				float v = ((y + randFloat()) / (imageHeight - 1.0));
				//float d = float(s) / float(sample);
				//float u = ((x + d) / (imageWidth - 1.0));
				//float v = ((y + d) / (imageHeight - 1.0));
				Ray ray = cam.get_ray(u, v);

				vec3 += rayColor(ray, background, scene, depth);
			}

			writeImage(vec3 * (1.0f / sample), output);
		}
	}
	cout << "\nRendered" << endl;

	output.close();
	return 0;
}
