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
	//printf("%lf %lf %lf\n", line.point.x, line.point.y, line.point.z);
	//printf("%lf %lf %lf\n", line.dir.x, line.dir.y, line.dir.z);
	
	if (time == 5) {
		//printf("time=3\n");
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
		//printf("%lf %lf %lf\n", crash_point->x, crash_point->y, crash_point->z);
		Color colorlight(0, 0, 0);
		for (int i = 0; i < lightnum; ++i) {
			colorlight += CalculateColor((*crash_point), line.dir, thing[p], (Pointlight*)light[i], p);
		}
		//printf("%lf %lf %lf\n", crash_point->x, crash_point->y, crash_point->z);
		
		Vec3 vecN = thing[p]->GetvecN(crash_point);
		line.point = Vec3(crash_point->x, crash_point->y, crash_point->z);
		line.dir = line.dir.Reflect(vecN);
		colorlight += Intersect(line, time + 1) * thing[p]->material.color * thing[p]->material.reflection;
		
		return colorlight;
	}
	else {//no crash
		//return Color(20, 20, 20);
		return Color(0, 0, 0);
	}
}

Color Raytracer::CalculateColor(Vec3 crash_point, Vec3 view_direction, Thing *thing, Pointlight *light, int p) {
	Vec3 l = (light->pos - crash_point).GetUnitVector();
	Vec3 vecN = thing->GetvecN(&crash_point);
	Vec3 r = l.Reflect(vecN);
	Color c = (0, 0, 0);
	if (thing->material.diffusion > 0) {
		double dot = l.Dot(vecN);
		if (dot > 0) {
			double diff = dot * thing->material.diffusion;
			c += thing->material.color * light->material.color * diff;
		}
	}
	if (thing->material.specular > 0) {
		double dot = r.Dot(view_direction);
		if (dot > 0) {
			c += light->material.color * thing->material.specular * pow(dot, 20);
		}
	}
	return c;
}

//phantom's code
/*
Primitive* light = p;
// calculate diffuse shading
vector3 L = ((Sphere*)light)->GetCentre() - pi;
NORMALIZE(L);
vector3 N = prim->GetNormal(pi);
if (prim->GetMaterial()->GetDiffuse() > 0)
{
	float dot = DOT(N, L);
	if (dot > 0)
	{
		float diff = dot * prim->GetMaterial()->GetDiffuse();
		// add diffuse component to ray color
		a_Acc += diff * prim->GetMaterial()->GetColor() * light->GetMaterial()->GetColor();
	}
}
*/