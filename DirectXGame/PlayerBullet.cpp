#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("sample.png");
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update() { worldTransform_.UpdateMatrix(); }

void PlayerBullet::Draw(const ViewProjection& viewprojection) { 
	model_->Draw(worldTransform_, viewprojection, textureHandle_); }
