#pragma once
#include "color.h"

class Material {
public:
	Color color;
	double reflection;
	double diffusion;

	Material();
	Material(Color _c, double _r, double _d);
};