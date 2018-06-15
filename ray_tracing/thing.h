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
	virtual bool Inside(Vec3 point);
	virtual double LengthInside(Vec3 vecN, Vec3 dir);
};

class Ball : public Thing {
public:
	double radius;
	Vec3 center;
	Ball(Vec3 _c, double _r, Material _m);
	Vec3* Crash(Vec3 source, Vec3 dir);
	Vec3 GetvecN(Vec3 *crash_point);
	bool Inside(Vec3 point);
	double LengthInside(Vec3 vecN, Vec3 dir);
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