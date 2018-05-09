#include "material.h"

Material::Material() :color(Color(0.2f, 0.2f, 0.2f)), reflection(0), diffusion(0.2f), specular(0.8f){}

Material::Material(Color _c, double _r, double _d)
{
	color = _c;
	reflection = _r;
	diffusion = _d;
	specular = 1.0f - diffusion;
}
