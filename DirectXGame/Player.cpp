#include "Player.h"

Player::~Player() {
	for (PlayerBullet* bullet : bullets_) {
		delete bullet;
	}
}

void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	input_ = Input::GetInstance();
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

	const float kMoveLimitX = 34;
	const float kMoveLimitY = 18;
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

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

	ImGui::Begin("debug");
	ImGui::SliderFloat3("position", &worldTransform_.translation_.x, -1000.0f, 1000.0f);
	ImGui::DragFloat3("rotate", &worldTransform_.rotation_.x, 0.01f);
	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	for (PlayerBullet* bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
	/*if (bullet_) {
		bullet_->Draw(viewProjection);
	}*/
}

void Player::Rotate() {
	const float kRotateSpeed = 0.2f;
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotateSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotateSpeed;
	}
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);
		velocity = TransformNomal(velocity, worldTransform_.matWorld_);
		/*if (bullet_) {
			delete bullet_;
			bullet_ = nullptr;
		}*/
		PlayerBullet* newBullet = new PlayerBullet();

		newBullet->Initialize(model_, this->worldTransform_.translation_, velocity);
		bullets_.push_back(newBullet);

		//bullet_ = newBullet;
	}
}

Vector3 Player::GetWorldPosition()
{
	Vector3 worldPos;
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];
	return worldPos;
}
