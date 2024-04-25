#pragma once
#include <WorldTransform.h>
//#include "Vector3AndMatrix4x4.h"
class Collider
{
public :
	float GetRadius() { return radius_; }
	void SetRadius(float radius) { radius_ = radius; }

	virtual void OnCollision();
	virtual Vector3 GetWorldPosition() = 0;
	
private:
	float radius_ = 10.0f;
};

