#include "RailCamera.h"




void RailCamera::Init(const Vector3& worldPos, const Vector3& rotate)
{
	worldTransfome_.Initialize();
	worldTransfome_.translation_ = worldPos;
	worldTransfome_.rotation_ = rotate;
	viewprojection_.farZ = 1000;
	viewprojection_.Initialize();
}

void RailCamera::Update()
{
	worldTransfome_.translation_ += velocity_;
	worldTransfome_.rotation_ += rotate_;
	//worldTransfome_.UpdateMatrix();
	
#ifdef _DEBUG
	ImGui::Begin("Camera");
	ImGui::DragFloat3("translate", &worldTransfome_.translation_.x, 0.1f);
	ImGui::DragFloat3("rotate", &worldTransfome_.rotation_.x, 0.1f);
	ImGui::End();
#endif // _DEBUG

	
	
	worldTransfome_.matWorld_ = MakeAffineMatrix(worldTransfome_.scale_, worldTransfome_.rotation_, worldTransfome_.translation_);

	viewprojection_.matView = Inverse(worldTransfome_.matWorld_);
}
