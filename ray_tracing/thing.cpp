#include "thing.h"

Ball::Ball(Vec3 _c, double _r, double _reflection, double _refration)
{
	center = _c;
	radius = _r;
	reflection_rate = _reflection;
	refraction_rate = _refration;
}

Vec3* Ball::Crash(Vec3 & source, Vec3 & dir)
{
	Vec3 l = center - source;
	if (l.Module() > radius) {//outside the ball;
		double tp = l.Dot(dir);
		if (tp > 0) {//cross maybe
			double d = sqrt(l.Module2() - tp*tp);
			if (d < radius) {//cross
				double r = sqrt(radius*radius - d*d);
				double distance = tp - d;
				Vec3 *crashpoint = &(source + tp * dir);
				return crashpoint;
			}
		}
	}
	return NULL;
}

Vec3 Ball::GetvecN(Vec3 * crash_point)
{
	return (*crash_point - center).GetUnitVector();
}

Plain::Plain(Vec3 _vecN, double _offset, double _reflection, double _refration)
{
	vecN = vecN;
	offset = _offset;
	reflection_rate = _reflection;
	refraction_rate = _refration;
}

Vec3* Plain::Crash(Vec3 & source, Vec3 & dir)
{
	double down = vecN.Dot(dir);
	if (down != 0) {
		double t = -(offset + (vecN.Dot(source))) / down;
		if (t > 0) {
			Vec3 *crashpoint = &(source + dir * t);
			return crashpoint;
		}
	}
	return NULL;
}

Vec3 Plain::GetvecN(Vec3 * crash_point)
{
	return vecN;
}
