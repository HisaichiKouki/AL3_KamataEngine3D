#pragma once

#include <memory>

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

#include "DebugCamera.h"
#include "Player.h"
#include "SkyDome.h"

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

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>

	ViewProjection viewProjection_;
	uint32_t textureHandle_ = 0;
	std::unique_ptr<Model> model_;
	// Model* model_ = nullptr;

	std::unique_ptr<Player> player_;

	std::unique_ptr<DebugCamera> debugCamera_;
	bool isDebugCameraActive;

	std::unique_ptr<Model> modelSkydome_;
	std::unique_ptr<SkyDome> skydome_;

	std::unique_ptr<Model> modelGround_;
	std::unique_ptr<SkyDome> ground_;
	// Player* player_ = nullptr;
};
