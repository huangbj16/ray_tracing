#pragma once
#include "vec3.h"

class Line {
public:
	Vec3 point, dir;

	Line(Vec3 _point, Vec3 _dir);
	Line() {}
};

class Camera {
public:
	Vec3 viewpoint;
	int n, m;
	Vec3 viewplain[1000][1000];//fixed
	Line viewlines[1000][1000];

	Camera(Vec3 _viewpoint, int _n, int _m, Vec3 **_viewplain);
	void CalculateLine();
};

