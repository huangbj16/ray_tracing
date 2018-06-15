#include "thing.h"


bool Thing::Inside(Vec3 point)
{
	return false;
}

double Thing::LengthInside(Vec3 vecN, Vec3 dir)
{
	return 10000.0f;
}

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
	
	else if(l.Module() < radius){//inside the ball;
		double LCos = l.Dot(dir.GetUnitVector());
		double dist = sqrt(radius*radius - l.Module2() + LCos*LCos) + LCos;
		Vec3 *crashpoint = new Vec3(source + dir*dist);
		return crashpoint;
	}
	
	return NULL;
}

Vec3 Ball::GetvecN(Vec3 * crash_point)
{
	return (*crash_point - center).GetUnitVector();
}

bool Ball::Inside(Vec3 point)
{
	double dist = (center - point).Module();
	if (dist < radius) return true;
	else return false;
}

double Ball::LengthInside(Vec3 vecN, Vec3 dir)
{
	double dot = -vecN.Dot(dir.GetUnitVector());
	if (dot > 0) {
		double CosI = sqrt(dot);
		return 2 * radius * CosI;
	}
	else return 0;
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

