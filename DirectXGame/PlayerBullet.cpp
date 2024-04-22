#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("sample.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void PlayerBullet::Update() { 
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ = Add(worldTransform_.translation_,velocity_);

	if (--deathTimer_<=0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewprojection) { 
	model_->Draw(worldTransform_, viewprojection, textureHandle_); }
