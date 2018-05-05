#pragma once
#include "vec3.h"
#include "color.h"

class Light {
public:
	Color color;
	virtual Color CalculateColor(Vec3 &point, Vec3 &dir, Vec3 &vecN) = 0;
	double roud, rous;
};

class Pointlight : public Light {
public:
	Vec3 pos;
	
	Pointlight(Color _color, Vec3 _pos);
	Color CalculateColor(Vec3 &point, Vec3 &dir, Vec3 &vecN);
};