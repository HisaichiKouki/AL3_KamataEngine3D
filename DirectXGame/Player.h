#pragma once
#include <cassert>
#include <Input.h>
#include "Model.h"
#include "WorldTransform.h"
#include "Vector3AndMatrix4x4.h"
#include <ImGuiManager.h>
#include <WinApp.h>
#include "PlayerBullet.h"
#include <ViewProjection.h>	

#include <stdlib.h>
#include <list>

#include "Collider.h"
#include <Sprite.h>

class GameScene;

class Player :public Collider
{
public:
	
	~Player();
	void Initialize(Model*model,uint32_t textureHandle, const Vector3& pos);
	void Update();
	void Draw(ViewProjection& viewProjection);
	void Rotate();
	void Attack();
	void AttackKeybord();
	void AttackController();
	void DrawUI();
	void ReticleMoveController();
	void MoveController();
	void MoveKeybord();
	void WorldToScreen();
	void ScreenToWorld();
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	Vector3 GetWorldPosition() override;
	Vector3 Get3DReticleWorldPosition() ;

	void SetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}
	void OnCollision() override;

	const std::list<PlayerBullet*>& GetBullets() const { return bullets_; }
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	void SetParent(const WorldTransform* parent);

	

private:
	WorldTransform worldTransform_;
	Model* model_ = nullptr;
	uint32_t textureHandle_ = 0u;
	Input* input_ = nullptr;
	PlayerBullet* bullet_ = nullptr;

	WorldTransform worldTransform3DReticle_;

	Sprite* sprite2Dreticle_ = nullptr;

	GameScene* gameScene_ = nullptr;
	const size_t shotCoolTime_ = 7;
	size_t isShotCount_;

	

	const ViewProjection* viewProjection_ = nullptr;
	std::list<PlayerBullet*> bullets_;


};
