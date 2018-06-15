#include "raytracer.h"
#include <Windows.h>

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
	Vec3 *crash_point = NULL;
	Vec3 *point = NULL;
	int p = -1;
	for (int i = 0; i < thingnum; ++i) {
		point = thing[i]->Crash(line.point, line.dir);
		if (point != NULL) {
			if (crash_point == NULL) {
				crash_point = point;
				p = i;
			}
			else if (crash_point->Distance2(line.point) > point->Distance2(line.point)) {
				crash_point = point;
				p = i;
			}
		}
	}
	if (crash_point != NULL) {
		Color colorlight(0, 0, 0);
		if (!thing[p]->Inside(line.point)) {//outside
			Vec3 check(-9.96, -4.4, 7.5);
			for (int i = 0; i < lightnum; ++i) {
				colorlight += CalculateColor((*crash_point), line.dir, thing[p], (Pointlight*)light[i], p);//calculate color at the point
			}
			Vec3 vecN = thing[p]->GetvecN(crash_point);
			if (thing[p]->material.reflection > 0) {
				Line newline;
				newline.dir = line.dir.Reflect(vecN);
				newline.point = (*crash_point) + newline.dir * EPS;
				colorlight += Intersect(newline, time + 1) * thing[p]->material.color * thing[p]->material.reflection;//calculate reflect color
			}
			if (thing[p]->material.refraction > 0) {//calculate refraction color
				double n = thing[p]->material.refraction_index;
				Line newline;
				n = 1 / n;
				newline.dir = line.dir.Refract(vecN, n);
				if (!newline.dir.IsZeroVector()) {
					newline.point = (*crash_point) + newline.dir * EPS;
					double absorb = exp((-0.01f) * thing[p]->LengthInside(vecN, newline.dir));
					colorlight += Intersect(newline, time + 1) * (thing[p]->material.refraction * absorb);
				}
			}
		}
		else {//inside
			Vec3 vecN = thing[p]->GetvecN(crash_point);
			double n = thing[p]->material.refraction_index;
			Line newline;
			newline.dir = line.dir.Refract(-vecN, n);
			if (!newline.dir.IsZeroVector()) {
				newline.point = (*crash_point) + newline.dir * EPS;
				colorlight += Intersect(newline, time + 1) * thing[p]->material.refraction;
			}
		}
		return colorlight;
	}
	else {//no crash
		return Color(0, 0, 0);
	}
}
Color Raytracer::CalculateColor(Vec3 crash_point, Vec3 view_direction, Thing *crash_thing, Pointlight *crash_light, int p) {
	Vec3 l = (crash_light->pos - crash_point).GetUnitVector();
	Vec3 vecN = crash_thing->GetvecN(&crash_point);
	Vec3 r = l.Reflect(vecN);
	Color c(0, 0, 0);
	//first calculate shadow;
	double dist = (crash_point - crash_light->pos).Module2();
	Vec3 *other_crash = NULL;
	for (int i = 0; i < thingnum; ++i) {
		if (i == p) continue;
		other_crash = thing[i]->Crash(crash_point, l);
		if (other_crash != NULL) {
			if (((*other_crash) - crash_point).Module2() < dist) {
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