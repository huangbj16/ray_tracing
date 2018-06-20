#include "raytracer.h"
#include <Windows.h>
#include <omp.h>

Raytracer::Raytracer(int _n, int _m, int _lightnum, int _thingnum)
{
	n = _n;
	m = _m;
	lightnum = _lightnum;
	thingnum = _thingnum;
	light = new Light*[lightnum];
	thing = new Thing*[thingnum];
}

void Raytracer::Calculate()
{
#pragma omp parallel for num_threads(8)
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			Line line = camera->viewlines[i][j];
			Color c = Intersect(line, 0);
			image[i][j] = c;
		}
	}
}

Color Raytracer::Intersect(Line line, int time) {
	if (time == 5) {
		return Color(0, 0, 0);//enough!
	}
	CrashBag crash_bag;
	CrashBag bag;
	int p = -1;
	for (int i = 0; i < thingnum; ++i) {
		bag = thing[i]->Crash(line.point, line.dir);
		if (!bag.crash_point.IsNullVector()) {
			if (crash_bag.crash_point.Distance2(line.point) > bag.crash_point.Distance2(line.point)) {
				crash_bag = bag;
				p = i;
			}
		}
	}
	if (!crash_bag.crash_point.IsNullVector()) {
		Color colorlight(0, 0, 0);
		if (!thing[p]->Inside(line.point)) {//outside
			Vec3 check(-9.96, -4.4, 7.5);
			for (int i = 0; i < lightnum; ++i) {
				colorlight += CalculateColor(crash_bag, line.dir, thing[p], (Pointlight*)light[i], p);//calculate color at the point
			}
			Vec3 vecN = crash_bag.vecN;
			if (thing[p]->material.reflection > 0) {
				Line newline;
				newline.dir = line.dir.Reflect(vecN);
				newline.point = bag.crash_point + newline.dir * EPS;
				colorlight += Intersect(newline, time + 1) * thing[p]->material.color * thing[p]->material.reflection;//calculate reflect color
			}
			if (thing[p]->material.refraction > 0) {//calculate refraction color
				double n = thing[p]->material.refraction_index;
				Line newline;
				n = 1 / n;
				newline.dir = line.dir.Refract(vecN, n);
				if (!newline.dir.IsZeroVector()) {
					newline.point = crash_bag.crash_point + newline.dir * EPS;
					double absorb = exp((-0.01f) * thing[p]->LengthInside(vecN, newline.dir));
					colorlight += Intersect(newline, time + 1) * (thing[p]->material.refraction * absorb);
				}
			}
		}
		else {//inside
			Vec3 vecN = crash_bag.vecN;
			double n = thing[p]->material.refraction_index;
			Line newline;
			newline.dir = line.dir.Refract(vecN, n);
			if (!newline.dir.IsZeroVector()) {
				newline.point = crash_bag.crash_point + newline.dir * EPS;
				colorlight += Intersect(newline, time + 1) * thing[p]->material.refraction;
			}
		}
		return colorlight;
	}
	else {//no crash
		return Color(0, 0, 0);
	}
}
Color Raytracer::CalculateColor(CrashBag bag, Vec3 view_direction, Thing *crash_thing, Pointlight *crash_light, int p) {
	Vec3 crash_point = bag.crash_point;
	Vec3 l = (crash_light->pos - crash_point).GetUnitVector();
	Vec3 vecN = bag.vecN;
	Vec3 r = l.Reflect(vecN);
	Color c(0, 0, 0);
	//first calculate shadow;
	double dist = l.Module2();
	CrashBag other_bag;
	for (int i = 0; i < thingnum; ++i) {
		if (i == p) continue;
		other_bag = thing[i]->Crash(crash_point, l);
		if (!other_bag.crash_point.IsNullVector()) {
			if ((other_bag.crash_point - crash_point).Module2() < dist) {
				return Color(0, 0, 0);
			}
		}
	}
	//no shadow, calculate diffusion and speculation
	if (crash_thing->material.diffusion > 0) {
		double dot = l.Dot(vecN);
		if (dot > 0) {
			double diff = dot * crash_thing->material.diffusion;
			c += crash_thing->material.color * crash_light->material.color * diff;
		}
	}
	if (crash_thing->material.specular > 0) {
		double dot = r.Dot(view_direction);
		if (dot > 0) {
			c += crash_light->material.color * crash_thing->material.specular * pow(dot, 20);
		}
	}
	return c;
}