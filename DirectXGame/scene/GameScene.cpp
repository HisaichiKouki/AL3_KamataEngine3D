#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"
GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete player_;
	delete debugCamera_;
	delete enemy_;
	delete skydome_;
	delete railCamera_;
	delete catmullromSpline;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	texHandle_ = TextureManager::Load("uvChecker.png");
	model_ = Model::Create();
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	player_ = new Player();
	Vector3 playerPosition(0, 0, 20.0f);
	player_->Initialize(model_, texHandle_, playerPosition);

	//player_->Initialize(model_, texHandle_);

	debugCamera_ = new DebugCamera(1280, 720);
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
	enemy_ = new Enemy();
	enemy_->SetPlayer(player_);
	enemy_->Initialize(model_, { 10,1,50.0f });

	skydome_ = new SkyDome();
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);
	skydome_->Init(modelSkydome_);
	railCamera_ = new RailCamera();
	railCamera_->Init({0.0f,0.0f,-50.0f}, player_->GetWorldTransform().rotation_);
	viewProjection_.matView = railCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;

	player_->SetParent(&railCamera_->GetWorldTransform());

	catmullromSpline = new CatmullRomSpline(debugCamera_->GetViewProjection());
}

void GameScene::Update() {
	railCamera_->Update();

	skydome_->Update();
	player_->Update();

	if (enemy_)
	{
		enemy_->Update();
	}

	CheckAllCollisions();
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_T)) {
		isDebugCameraActive = true;
	}
	if (isDebugCameraActive) {
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.matView = railCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = railCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
		//viewProjection_.UpdateMatrix();
	}
#endif // _DEBUG
	
	
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
	player_->Draw(viewProjection_);
	if (enemy_)
	{
		enemy_->Draw(viewProjection_);
	}

	catmullromSpline->Draw();
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

void GameScene::CheckAllCollisions()
{
	//Vector3 posA, posB;

	const std::list<PlayerBullet*>& playerBullets_ = player_->GetBullets();
	const std::list<EnemyBullet*>& enemyBullets_ = enemy_->GetBullets();

	//posA = player_->GetWorldPosition();

	
#pragma region playerToEnemyBullet
	for (auto* bullet : enemyBullets_)
	{
		
		CheckCollisionPair(player_, bullet);
		
	}
	/*for (auto* bullet : enemyBullets_)
	{
		posB = bullet->GetWorldPosition();

		if (Length(posA, posB) <= 16.0f)
		{
			player_->OnCollision();
			bullet->OnCollision();
		}
	}*/
#pragma endregion

#pragma region PlayerBulletToEnemy
	for (auto* bullet : playerBullets_)
	{

		CheckCollisionPair(enemy_, bullet);

	}
	/*posA = enemy_->GetWorldPosition();
	for (auto* bullet : playerBullets_)
	{
		posB = bullet->GetWorldPosition();

		if (Length(posA, posB) <= 10.0f)
		{
			enemy_->OnCollision();
			bullet->OnCollision();
		}
	}*/
#pragma endregion


#pragma region playerBulletToEnemyBullet
	for (auto* playerBullet : playerBullets_)
	{

		for (auto* enemyBullet : enemyBullets_)
		{
			CheckCollisionPair(playerBullet, enemyBullet);

		}


	}
	/*for (auto* playerBullet : playerBullets_)
	{
		posA = playerBullet->GetWorldPosition();

		for (auto* enemyBullet : enemyBullets_)
		{
			posB = enemyBullet->GetWorldPosition();


			if (Length(posA, posB) <= 10.0f)
			{
				playerBullet->OnCollision();
				enemyBullet->OnCollision();
			}
		}

		
	}*/
#pragma endregion

}

void GameScene::CheckCollisionPair(Collider* colliderA, Collider* colliderB)
{
	colliderA->GetWorldPosition();
	colliderB->GetWorldPosition();

	float distance = Length(colliderA->GetWorldPosition(), colliderB->GetWorldPosition());

	if (distance<=colliderA->GetRadius()+ colliderB->GetRadius())
	{
		colliderA->OnCollision();
		colliderB->OnCollision();
	}
}

