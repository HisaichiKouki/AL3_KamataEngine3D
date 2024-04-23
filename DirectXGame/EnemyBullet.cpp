#include "EnemyBullet.h"

void EnemyBullet::Initialize(Model* model, const Vector3& position)
{
	assert(model);
	model_ = model;
	textureHandle_ = TextureManager::Load("./Resources/addTexture/bullet.png");

	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	
	//velocity_ = velocity;
}

void EnemyBullet::Update()
{
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
