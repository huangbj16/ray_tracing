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
	Light **light;
	int lightnum;
	Thing **thing;
	int thingnum;

	Raytracer(int _n, int _m, int _lightnum, int _thingnum);
	void Calculate();
	Color Intersect(Line line, int time);
	Color CalculateColor(Vec3 crash_point, Vec3 view_direction, Thing *thing, Pointlight *light, int p);
};