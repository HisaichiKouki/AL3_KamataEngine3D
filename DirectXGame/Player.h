#pragma once

#include <cassert>

#include <Model.h>
#include <WorldTransform.h>
#include <ViewProjection.h>

class Player {
public:
	Player();
	~Player();

	void Init(Model*model,uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjecton);

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
};
