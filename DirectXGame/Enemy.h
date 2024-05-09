#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"
#include <stdlib.h>

#include "EnemyBullet.h"
#include "TimedCall.h"

#include "Collider.h"
class Player;
class GameScene;
enum class Phase
{
	Approach,
	Leave,
};
class Enemy: public Collider
{

public:
	~Enemy();
	void Initialize(Model* model, const Vector3& position);
	void Update();
	void Draw(const ViewProjection& viewprojection);
	void SwitchPhase();
	void ApproachInitialize();
	void ApproachMove();
	void LeaveMove();

	void Fire();
	void FireReset();

	void SetPlayer(Player* player) { player_ = player; }
	Vector3 GetWorldPosition() override;

	void OnCollision() override;

	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_;

	const float kMoveSpeed = 0.01f;
	const float kBulletSpeed = 0.4f;
	float homingPower = 0.001f;
	Vector3 velocity_{ 0,0,-kMoveSpeed };

	Phase phase_ = Phase::Approach;

	Vector3 approachVelocity_{ 0,0,-kMoveSpeed };
	Vector3 leaveVelocity_{ -kMoveSpeed * 0.7f,kMoveSpeed * 0.7f,0 };

	//void (Enemy::* pFunc)();
	static void(Enemy::* spFuncTable[])();

	std::list<TimedCall*>timedCalls_;
	//std::list<EnemyBullet*>bullets_;

	Player* player_ = nullptr;

	GameScene* gameScene_ = nullptr;

public:
	static const int32_t kFireCoolTime = 30 * 1;


};