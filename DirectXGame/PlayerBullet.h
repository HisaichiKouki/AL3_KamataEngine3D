#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include <assert.h>
#include "TextureManager.h"
class PlayerBullet {
public:
	void Initialize(Model* model, const Vector3& position);
	void Update();
	void Draw(const ViewProjection& viewprojection);
	private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
};
