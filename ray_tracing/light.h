#pragma once
#include "vec3.h"
#include "color.h"
#include "material.h"

class Light {
public:
	Material material;

	Light() {}
	Light(Material _m) :material(_m) {}
};

class Pointlight : public Light {
public:
	Vec3 pos;
	
	Pointlight(Material _m, Vec3 _pos);
};