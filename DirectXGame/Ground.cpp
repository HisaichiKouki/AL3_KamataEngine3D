#include "Ground.h"

Ground::~Ground() {}

void Ground::Init(Model* model) {
	model_ = model;
	worldTransform_.Initialize();
}

void Ground::Update() {}

void Ground::Draw(const ViewProjection& viewProjection) { model_->Draw(worldTransform_, viewProjection); }
