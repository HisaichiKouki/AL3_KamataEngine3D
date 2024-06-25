#include "SkyDome.h"



SkyDome::~SkyDome()
{
	
}

void SkyDome::Init( Model* model)
{
	model_ = model;
	worldTransform_.Initialize();

}

void SkyDome::Update()
{
}

void SkyDome::Draw(const ViewProjection& viewProjection)
{
	model_->Draw(worldTransform_, viewProjection);
}
