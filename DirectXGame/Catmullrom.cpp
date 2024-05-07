#include "Catmullrom.h"

void Catmullrom::Init(std::vector<Vector3> controlPoints)
{
	
}

void Catmullrom::Draw(std::vector<Vector3> controlPoints, float t)
{
}

Vector3 Catmullrom::CatmullromSprit(std::vector<Vector3> controlPoints, float t)
{
	spritNum_ = (int)controlPoints.size();
	divisionSize_ = 1.0f / (float)spritNum_;
	if (t<divisionSize_)
	{
		return HermiteSprit(controlPoints[0], controlPoints[0], controlPoints[1], controlPoints[2], t);
	}
	if (t > divisionSize_ * (spritNum_ - 1)) 
	{
		return HermiteSprit(controlPoints[1], controlPoints[2], controlPoints[3], controlPoints[3], t);
	}

	for (int i = 0; i < divisionSize_; i++)
	{
		if (t)
		{

		}
	}
	return Vector3();
}

Vector3 Catmullrom::HermiteSprit(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3, float t)
{
	Vector3 result{};
	result = (p0 * -1 + p1 * 3 + p2 * -3 + p3) * t * t * t + (p0 * 2 + p1 * -5 + p2 * 4 + p3 * -1) * t * t + (p0 * -1 + p2) * t + p1 * 2;
	return result;
}


//Vector3 Catmullrom::CatmullromSprine(std::vector<Vector3> controlPoints, float t)
//{
//
//	int l = controlPoints.size();
//	float progress = (l - 1) * t;
//	int i = int(progress);
//	float weight = progress - i;
//
//	return Vector3();
//}
