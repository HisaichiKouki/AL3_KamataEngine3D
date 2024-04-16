#pragma once
#include <cassert>
#include <Input.h>
#include "Model.h"
#include "WorldTransform.h"
#include "Vector3AndMatrix4x4.h"
#include <ImGuiManager.h>
#include "PlayerBullet.h"
class Player {
public:
	void Initialize(Model*model,uint32_t textureHandle);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void Rotate();
	void Attack();

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	PlayerBullet* bullet_ = nullptr;
};
