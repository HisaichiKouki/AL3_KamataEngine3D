#include "Easing.h"

Vector3 Lerp(const Vector3& from, const Vector3& to, float t)
{
	Vector3 result{};
	result.x = from.x + t * (to.x - from.x);
	result.y = from.y + t * (to.y - from.y);
	result.z = from.z + t * (to.z - from.z);
	return result;
}

Vector3 SLerp(const Vector3& from, const Vector3& to, float t)
{
	Vector3 fromVec = Normalize(from);
	Vector3 toVec = Normalize(to);

	float dot = Dot(from,to);

	if (dot>0.99995f)
	{
		return to;
	}

	float theta = std::acos(dot);
	float sinTheta = std::sin(theta);
	float invSinTheta = 1.0f / sinTheta;
	float coeff0 = std::sin((1.0f - t) * theta) * invSinTheta;
	float coeff1 = std::sin(t * theta) * invSinTheta;

	// Slerpの結果を計算する
	return from * coeff0 + to * coeff1;

}
