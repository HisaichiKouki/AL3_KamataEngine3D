#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity)
{
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("./Resources/addTexture/bullet.png");

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	velocity_ = velocity;
	//velocity_ = velocity;
	worldTransform_.scale_.x = 0.5f;
	worldTransform_.scale_.y = 0.5f;
	worldTransform_.scale_.z = 3.0f;
}

void EnemyBullet::Update()
{
	float vecLength = sqrtf(velocity_.x * velocity_.x + velocity_.z * velocity_.z);
	worldTransform_.rotation_.y = std::atan2( velocity_.x, velocity_.z);

	worldTransform_.rotation_.x = std::atan2(-velocity_.y, vecLength);

	if (--deathTimer_<0)
	{
		isDead_ = true;
	}
	worldTransform_.translation_ += velocity_;
	worldTransform_.UpdateMatrix();
}

void EnemyBullet::Draw(const ViewProjection& viewprojection)
{
	model_->Draw(worldTransform_, viewprojection, textureHandle_);
}
