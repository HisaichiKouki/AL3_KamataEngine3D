#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include <stdlib.h>

#include "EnemyBullet.h"

enum class Phase
{
	Approach,
	Leave,
};
class Enemy {

public:
	~Enemy();
	void Initialize(Model*model,const Vector3& position);
	void Update();
	void Draw(const ViewProjection& viewprojection);
	void SwitchPhase();
	void ApproachInitialize();
	void ApproachMove();
	void LeaveMove();

	void Fire();
	
private:
	WorldTransform worldTransform_;
	Model* model_=nullptr;
	uint32_t textureHandle_;

	float kMoveSpeed = 0.2f;
	Vector3 velocity_{ 0,0,-kMoveSpeed };

	Phase phase_ = Phase::Approach;

	Vector3 approachVelocity_{ 0,0,-kMoveSpeed };
	Vector3 leaveVelocity_{ -kMoveSpeed*0.7f,kMoveSpeed * 0.7f,0 };

	//void (Enemy::* pFunc)();
	static void(Enemy::* spFuncTable[])();


	std::list<EnemyBullet*>bullets_;

	int32_t isFireCoolTime = 0;

public:
	static const int32_t kFireCoolTime = 60 * 1;


};
