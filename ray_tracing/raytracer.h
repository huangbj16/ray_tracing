#pragma once
#include "vec3.h"
#include "color.h"
#include "camera.h"
#include "light.h"
#include "thing.h"

class Raytracer {
public:
	Color image[1000][1000];
	int n, m;
	Camera *camera;
	Light *light;
	Thing *thing;

	void Calculate();
	Color Intersect(Line &line);
};