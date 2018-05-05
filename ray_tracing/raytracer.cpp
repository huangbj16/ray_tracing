#include "raytracer.h"

void Raytracer::Calculate()
{
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			Line line = camera->viewlines[i][j];
			Color c = Intersect(line);
			image[i][j] = c;
		}
	}
}

Color Raytracer::Intersect(Line &line) {
	Vec3 *crash_point = thing->Crash(line.point, line.dir);
	if (crash_point != NULL) {
		//printf("flag\n");
		Color colorlight = light->CalculateColor(line.point, line.dir, thing->GetvecN(crash_point));
		Color c = colorlight * thing->reflection_rate;
		Vec3 vecN = thing->GetvecN(crash_point);
		line.point = (*crash_point);
		line.dir = line.dir.Reflect(vecN);
		c += Intersect(line);
		return c;
	}
	else {//no crash
		return Color(20, 20, 20);
	}
}