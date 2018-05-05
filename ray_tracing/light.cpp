#include "light.h"

Pointlight::Pointlight(Color _color, Vec3 _pos)
{
	color = _color;
	pos = _pos;
	roud = 1;
	rous = 1;
}

Color Pointlight::CalculateColor(Vec3 &point, Vec3 &dir, Vec3 &vecN)//phongÄ£ÐÍ
{
	Vec3 l = point - pos;
	Vec3 rdir = Vec3(-dir.x, -dir.y, -dir.z).GetUnitVector();
	Vec3 r = l.Reflect(vecN);
	return Color(255, 255, 255) * (roud + rous * r.Dot(rdir) / vecN.GetUnitVector().Dot(l)) ;
}
