#pragma once
#include <WorldTransform.h>
#include <ViewProjection.h>
#include <Model.h>
class SkyDome
{
public:
	~SkyDome();
	void Init(Model* model);
	void Update();
	void Draw(const ViewProjection& viewProjection);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;

};

