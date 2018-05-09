#include "thing.h"

Ball::Ball(Vec3 _c, double _r, Material _m)
{
	center = _c;
	radius = _r;
	material = _m;
}

Vec3* Ball::Crash(Vec3 source, Vec3 dir)
{
	Vec3 l = center - source;
	if (l.Module() > radius) {//outside the ball;
		double tp = l.Dot(dir);
		if (tp > 1e-6) {//cross maybe
			double d = sqrt(l.Module2() - tp*tp);
			if (d < radius) {//cross
				double r = sqrt(radius*radius - d*d);
				double distance = tp - r;
				Vec3 *crashpoint = new Vec3;
				(*crashpoint) = (source + dir * distance);
				//crashpoint->Print();
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

Plain::Plain(Vec3 _vecN, double _offset, Material _m)
{
	vecN = _vecN;
	offset = _offset;
	material = _m;
}

Vec3* Plain::Crash(Vec3 source, Vec3 dir)
{
	double down = vecN.Dot(dir);
	//printf("%lf ", down);
	if (fabs(down) >= EPS) {
		double t = -(offset + (vecN.Dot(source))) / down;
		if (t > EPS) {
			Vec3 *crashpoint = new Vec3;
			(*crashpoint) = (source + dir * t);
			return crashpoint;
		}
	}
	return NULL;
}

Vec3 Plain::GetvecN(Vec3 * crash_point)
{
	return vecN;
}
