#pragma once
#include "CatmullRom.h"

class CatmullRomSpline
{
public:
	CatmullRomSpline();
	void Init();
	void Update();
	void Draw();
private:
	std::vector<Vector3> controlPoints_;
	
};

