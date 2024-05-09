#include "CatmullRomSpline.h"

CatmullRomSpline::CatmullRomSpline(const ViewProjection& viewprojection)
{
	Init();
	PrimitiveDrawer::GetInstance()->SetViewProjection(&viewprojection);
}

void CatmullRomSpline::Init()
{
	controlPoints_ = {
		{0,0,0},
		{10,10,0},
		{10,15,0},
		{20,15,0},
		{20,0,0},
		{30,0,0}
	};
}

void CatmullRomSpline::Draw()
{

	for (size_t i = 0; i < segmentCount_; i++)
	{
		float t = 1.0f / segmentCount_ * i;
		Vector3 pos = CatmullRomPosition(controlPoints_, t);
		pointsDrawing_.push_back(pos);
	}

	for (size_t i = 0; i < segmentCount_-1; i++)
	{
		PrimitiveDrawer::GetInstance()->DrawLine3d(pointsDrawing_[i], pointsDrawing_[i + 1], { 1.0f,1.0f,1.0f,1.0f});
	}

}

