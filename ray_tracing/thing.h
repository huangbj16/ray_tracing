#pragma once
#include "vec3.h"
#include "dir2.h"
#include "material.h"
#include <cmath>
#include <stdio.h>

class Thing {
public:
	Material material;

	virtual Vec3* Crash(Vec3 source, Vec3 dir) = 0;
	virtual Vec3 GetvecN(Vec3 *crash_point) = 0;
};

class Ball : public Thing {
private:
	double radius;
	Vec3 center;
public:
	Ball(Vec3 _c, double _r, Material _m);
	Vec3* Crash(Vec3 source, Vec3 dir);
	Vec3 GetvecN(Vec3 *crash_point);
};

class Plain : public Thing {
private://vecN * X + offset = 0
	double offset;
	Vec3 vecN;
public:
	Plain(Vec3 _vecN, double _offset, Material _m);
	Vec3* Crash(Vec3 source, Vec3 dir);
	Vec3 GetvecN(Vec3 *crash_point);
};