#pragma once
#include "CatmullRom.h"
#include "PrimitiveDrawer.h"
#include <ViewProjection.h>
class CatmullRomSpline
{
public:
	CatmullRomSpline(const ViewProjection& viewprojection);
	void Init();
	void Update();
	void Draw();
private:
	std::vector<Vector3> controlPoints_;
	std::vector<Vector3> pointsDrawing_;
	const size_t segmentCount_ = 100;
};

