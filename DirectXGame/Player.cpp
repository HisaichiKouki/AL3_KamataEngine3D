#include "Player.h"


void Player::Initialize(Model* model, uint32_t textureHandle) {
	assert(model);
	model_ = model;
	textureHandle_ = textureHandle;

	worldTransform_.Initialize();
	input_ = Input::GetInstance();
}

void Player::Update() {
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


	//worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);

		//worldTransform_.TransferMatrix();
	worldTransform_.UpdateMatrix();

		ImGui::Begin("debug");
	    ImGui::SliderFloat3("position", &worldTransform_.translation_.x, -1000.0f, 1000.0f);
	    ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection, textureHandle_); }

void Player::Rotate() { const float kRotateSpeed = 0.2f;
	if (input_->PushKey(DIK_A)) {
		worldTransform_.rotation_.y -= kRotateSpeed;
	} else if (input_->PushKey(DIK_D)) {
		worldTransform_.rotation_.y += kRotateSpeed;

	}
}

