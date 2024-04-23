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
	//worldTransform_.translation_ += velocity_;
	SwitchPhase();
}

void Enemy::Draw(const ViewProjection& viewprojection) {

	model_->Draw(worldTransform_, viewprojection, textureHandle_);
}

void Enemy::SwitchPhase()
{
	switch (phase_)
	{
	case Phase::Approach:
		ApproachMove();
		break;
	case Phase::Leave:
		LeaveMove();
		break;
	default:
		break;
	}
}

void Enemy::ApproachMove()
{
	worldTransform_.translation_ += approachVelocity_;
	if (worldTransform_.translation_.z<0.0f)
	{
		phase_ = Phase::Leave;
	}
}

void Enemy::LeaveMove()
{
	worldTransform_.translation_ += leaveVelocity_;
}
