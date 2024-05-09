#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "Player.h"
#include "DebugCamera.h"
#include "Enemy.h"
#include "SkyDome.h"
#include "RailCamera.h"
#include "CatmullRomSpline.h"

#include <sstream>

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void CheckAllCollisions();
	const std::list<EnemyBullet*>& GetBullets() const { return enemyBullets_; }

	void AddEnemyBullet(EnemyBullet* enemyBullet);

	void LoadEnemyPopDate();
	void UpdateEnemyPopCommands();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	uint32_t texHandle_ = 0;
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	Player* player_ = nullptr;

	bool isDebugCameraActive = false;
	DebugCamera* debugCamera_ = nullptr;
	RailCamera* railCamera_ = nullptr;

	std::list<Enemy*>enemys_;
	//Enemy* enemy_ = nullptr;

	Model* modelSkydome_ = nullptr;
	SkyDome* skydome_ = nullptr;
	
	//CatmullRomSpline* catmullromSpline = nullptr;

	std::list<EnemyBullet*>enemyBullets_;

	std::stringstream enemyPopCommands;
	
	bool isEnemySpown_ = false;
	int32_t isEnemySpownWaitTime_;
private:
	
	/// <summary>
	/// コライダー２つの衝突判定と応答
	/// </summary>
	/// <param name="colliderA"></param>
	/// <param name="colliderB"></param>
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
};
