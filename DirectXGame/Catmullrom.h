#pragma once
#include "Easing.h"
#include <Vector3AndMatrix4x4.h>
#include <PrimitiveDrawer.h>
#include <stdio.h>
//#include <list>
#include <vector>
class Catmullrom
{

public:
	void Init(std::vector<Vector3>controlPoints);
	void Update();
	void Draw(std::vector<Vector3>controlPoints,float t);
	Vector3 CatmullromSprit(std::vector<Vector3>controlPoints,float t);
	Vector3 HermiteSprit(Vector3 p0, Vector3 p1, Vector3 p2, Vector3 p3,float t);

private:
	float divisionSize_;//1をcontrolPoints_.sizeで割った値
	float spritNum_;
};

