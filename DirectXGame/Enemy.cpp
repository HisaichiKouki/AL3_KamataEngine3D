#include "Enemy.h"

void Enemy::Initialize(Model* model, const Vector3& position) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	textureHandle_ = TextureManager::Load("sample.png");

}

void Enemy::Update() {
	//worldTransform_.translation_ = Add(worldTransform_.translation_,velocity_);
	worldTransform_.UpdateMatrix();
	worldTransform_.translation_ += velocity_;
}

void Enemy::Draw(const ViewProjection& viewprojection) {

	model_->Draw(worldTransform_, viewprojection, textureHandle_);
}

void Enemy::SwitchPhase()
{
	switch (phase_)
	{
	case Phase::Approach:
		worldTransform_.translation_ += velocity_;
		break;
	case Phase::Leave:
		break;
	default:
		break;
	}
}
