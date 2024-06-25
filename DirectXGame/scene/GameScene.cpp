#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <AxisIndicator.h>

GameScene::GameScene() {}

GameScene::~GameScene() {
	 }

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	textureHandle_ = TextureManager::Load("uvChecker.png");
	model_ = std::make_unique<Model>();
	model_.reset(Model::Create());
	//model_ = Model::Create();
	viewProjection_.Initialize();
	player_ = std::make_unique<Player>();
	//player_ = new Player();
	player_->Init(model_.get(), textureHandle_);

	debugCamera_ = std::make_unique<DebugCamera>(1280, 720);
	
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);

	skydome_ = std::make_unique<SkyDome>();
	modelSkydome_ = std::make_unique<Model>();
	modelSkydome_.reset(Model::CreateFromOBJ("skydome", true));
	//modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	skydome_->Init(modelSkydome_.get());

	ground_ = std::make_unique<SkyDome>();
	modelGround_ = std::make_unique<Model>();
	modelGround_.reset(Model::CreateFromOBJ("ground", true));
	ground_->Init(modelGround_.get());
	isDebugCameraActive = false;
}

void GameScene::Update() {
	player_->Update();
	skydome_->Update();
	ground_->Update();


#ifdef _DEBUG
	if (input_->TriggerKey(DIK_T)) {
		isDebugCameraActive = !isDebugCameraActive;
	}
#endif // _DEBUG
	if (isDebugCameraActive) {

		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();

	} else {
		/*viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();*/
		// viewProjection_.UpdateMatrix();
	}
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>
	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	skydome_->Draw(viewProjection_);
	ground_->Draw(viewProjection_);

	player_->Draw(viewProjection_);
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
