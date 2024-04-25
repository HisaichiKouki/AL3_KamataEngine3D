#pragma once
#include <WorldTransform.h>
#include <Model.h>

#include <Vector3.h>
#include <ViewProjection.h>
#include <TextureManager.h>
#include <assert.h>

#include <stdlib.h>

#include "Easing.h"
#include "imgui.h"

#include "Collider.h"

class Player;
class EnemyBullet:public Collider
{
public:
	void Initialize(Model*model,const Vector3& position,const Vector3& velocity);
	void Update();
	void Draw(const ViewProjection& viewprojection);
	bool IsDead() const { return isDead_; }
	Vector3 GetWorldPosition()override;
	void SetPlayer(Player* player) { player_ = player; }
	void SetHomingPower(float power) { homingPower = power; }

	void OnCollision() override;


private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;

	float kSpeed = 0.4f;
	Vector3 velocity_ = { 0,0,-kSpeed };

	static const uint32_t kLifeTime = 60 * 3;
	int32_t deathTimer_ = kLifeTime;
	bool isDead_=false;



	Player* player_ = nullptr;
	float homingPower = 0.01f;



};

