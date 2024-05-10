#include "Player.h"

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
	delete sprite2Dreticle_;
}

void Player::Initialize(Model* model, uint32_t textureHandle, const Vector3& pos) {
	assert(model);

	model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	worldTransform_.translation_ = pos;
	input_ = Input::GetInstance();
	worldTransform3DReticle_.Initialize();

	uint32_t textureReticle = TextureManager::Load("./Resources/addTexture/reticle.png");
	sprite2Dreticle_ = Sprite::Create(
		textureReticle, { 0,0 }, {1,1,1,1}, { 0.5, 0.5 });

	isShotCount_ = 0;
}

void Player::Update() {

	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->IsDead()) {
			delete bullet;
			return true;
		}
		return false;
	});

	Vector3 move = {0, 0, 0};
	const float kCharacterSpeed = 0.2f;

	if (input_->PushKey(DIK_LEFTARROW)) {
		move.x -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_RIGHTARROW)) {
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey(DIK_DOWNARROW)) {
		move.y -= kCharacterSpeed;
	} else if (input_->PushKey(DIK_UPARROW)) {
		move.y += kCharacterSpeed;
	}
	Rotate();

	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	const float kMoveLimitX = 12;
	const float kMoveLimitY = 6;
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	const float kDistancePlayerTo3DReticle = 50.0f;
	Vector3 offset = { 0,0,1.0f };

	offset = TransformNomal(offset, worldTransform_.parent_->matWorld_);
	offset = Normalize(offset) * kDistancePlayerTo3DReticle;

	Attack();
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
	/*if (bullet_) {
		bullet_->Update();
	}*/
	// worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

	// worldTransform_.TransferMatrix();

	worldTransform_.UpdateMatrix();

	worldTransform3DReticle_.translation_ = Transform(offset, worldTransform_.matWorld_);

	worldTransform3DReticle_.UpdateMatrix();

	ImGui::Begin("debug");
	ImGui::SliderFloat3("position", &worldTransform_.translation_.x, -1000.0f, 1000.0f);
	ImGui::SliderFloat3("3DReticleposition", &worldTransform3DReticle_.translation_.x, -1000.0f, 1000.0f);
	ImGui::DragFloat3("rotate", &worldTransform3DReticle_.rotation_.x, 0.01f);
	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	//model_->Draw(worldTransform3DReticle_, viewProjection, textureHandle_);
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
	/*if (bullet_) {
		bullet_->Draw(viewProjection);
	}*/
}

void Player::Rotate() {
	const float kRotateSpeed = 0.01f;
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotateSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotateSpeed;
	}
	if (input_->PushKey(DIK_W)) {
		worldTransform_.rotation_.x -= kRotateSpeed;
	}
	else if (input_->PushKey(DIK_S)) {
		worldTransform_.rotation_.x += kRotateSpeed;
	}
}

void Player::Attack() {
	
	if (isShotCount_>0)
	{
		isShotCount_--;
		return;
	}

	if (input_->PushKey(DIK_SPACE)) {

		isShotCount_ = shotCoolTime_;
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		velocity = Subtract(Get3DReticleWorldPosition(), GetWorldPosition());
		velocity = Normalize(velocity) * kBulletSpeed;
		//velocity = TransformNomal(velocity, worldTransform_.matWorld_);
		/*if (bullet_) {
			delete bullet_;
			bullet_ = nullptr;
		}*/
		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(model_, this->GetWorldPosition(), velocity);
		bullets_.push_back(newBullet);

		//bullet_ = newBullet;
	}
}

void Player::DrawUI()
{
	WorldToScreen();
	sprite2Dreticle_->Draw();
}

void Player::WorldToScreen()
{
	Vector3 positionReticle = Get3DReticleWorldPosition();
	Matrix4x4 matViewport = MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
	Matrix4x4 matViewProjectionViewport = Multiply(
		Multiply(viewProjection_->matView, viewProjection_->matProjection), matViewport);
	positionReticle = Transform(positionReticle, matViewProjectionViewport);
	sprite2Dreticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));
}

Vector3 Player::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}

Vector3 Player::Get3DReticleWorldPosition()
{
	Vector3 worldPos;
	worldPos.x = worldTransform3DReticle_.matWorld_.m[3][0];
	worldPos.y = worldTransform3DReticle_.matWorld_.m[3][1];
	worldPos.z = worldTransform3DReticle_.matWorld_.m[3][2];
	return worldPos;
}


void Player::OnCollision()
{
}

void Player::SetParent(const WorldTransform* parent)
{
	worldTransform_.parent_ = parent;
}
