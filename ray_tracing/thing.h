#pragma once
#include "vec3.h"
#include "dir2.h"
#include <cmath>

class Thing {
public:
	double reflection_rate, refraction_rate;//œ»≤ªøº¬«’€…‰°£

	virtual Vec3* Crash(Vec3 &source, Vec3 &dir) = 0;
	virtual Vec3 GetvecN(Vec3 *crash_point) = 0;
};

class Ball : public Thing {
private:
	double radius;
	Vec3 center;
public:
	Ball(Vec3 _c, double _r, double _reflection, double _refration);
	virtual Vec3* Crash(Vec3 &source, Vec3 &dir);
	virtual Vec3 GetvecN(Vec3 *crash_point);
};

class Plain : public Thing {
private:
	double offset;
	Vec3 vecN;
public:
	Plain(Vec3 _vecN, double _offset, double _reflection, double _refration);
	virtual Vec3* Crash(Vec3 &source, Vec3 &dir);
	virtual Vec3 GetvecN(Vec3 *crash_point);
};