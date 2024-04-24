#pragma once

/// <summary>
/// 3次元ベクトル
/// </summary>
struct Vector3 final {
	float x;
	float y;
	float z;


	const Vector3 operator+(const Vector3& v1) 
	{
		return Vector3(this->x + v1.x, this->y + v1.y, this->z + v1.z);
	}

	Vector3& operator+=(const Vector3& v1) 
	{
		this->x += v1.x;
		this->y += v1.y;
		this->z += v1.z;
		return *this;
	}
	Vector3& operator-=(const Vector3& v1)
	{
		this->x -= v1.x;
		this->y -= v1.y;
		this->z -= v1.z;
		return *this;
	}
	Vector3& operator*=(const Vector3& v1)
	{
		this->x *= v1.x;
		this->y *= v1.y;
		this->z *= v1.z;
		return *this;
	}
	Vector3& operator/=(const Vector3& v1)
	{
		this->x /= v1.x;
		this->y /= v1.y;
		this->z /= v1.z;
		return *this;
	}
};