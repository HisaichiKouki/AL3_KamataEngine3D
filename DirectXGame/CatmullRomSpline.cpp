#include "CatmullRomSpline.h"

CatmullRomSpline::CatmullRomSpline()
{
	Init();
}

void CatmullRomSpline::Init()
{
	controlPoints_ = {
		{0,0,0},
		{0,0,0}
	};
}
