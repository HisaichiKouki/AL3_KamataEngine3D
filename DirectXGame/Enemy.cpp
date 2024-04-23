#include "Enemy.h"

Enemy::~Enemy()
{
	for (EnemyBullet* bullet : bullets_)
	{
		delete bullet;
	}

	for (auto& timedCall:timedCalls_)
	{
		delete timedCall;
	}
}

void Enemy::Initialize(Model* model, const Vector3& position) {
	model_ = model;
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	textureHandle_ = TextureManager::Load("sample.png");
	//pFunc = &Enemy::ApproachMove;
	//Fire();
	ApproachInitialize();
}

void Enemy::Update() {


	bullets_.remove_if([](EnemyBullet* bullet) {
		if (bullet->IsDead())
		{
			delete bullet;
			return true;
		}
		return false;
		});

	(this->*spFuncTable[static_cast<size_t>(phase_)])();

	//worldTransform_.translation_ = Add(worldTransform_.translation_,velocity_);
	worldTransform_.UpdateMatrix();
	//worldTransform_.translation_ += velocity_;
	//SwitchPhase();
	//(this->*pFunc)();

	for (EnemyBullet* bullet : bullets_)
	{
		bullet->Update();
	}

}

void Enemy::Draw(const ViewProjection& viewprojection) {

	model_->Draw(worldTransform_, viewprojection, textureHandle_);
	for (EnemyBullet* bullet : bullets_)
	{
		bullet->Draw(viewprojection);
	}
}

void Enemy::SwitchPhase()
{
	//pFunc = &Enemy::ApproachMove;
	/*switch (phase_)
	{
	case Phase::Approach:
		ApproachMove();
		break;
	case Phase::Leave:
		LeaveMove();
		break;
	default:
		break;
	}*/
}

void Enemy::ApproachInitialize()
{
	FireReset();
}

void Enemy::ApproachMove()
{

	timedCalls_.remove_if([](TimedCall* timedCall) {
		if (timedCall->IsFinished()) {
			delete timedCall;
			return true;
		}
		return false;
		});
	for (auto& timedCall : timedCalls_)
	{
		timedCall->Update();
	}
	/*if (--isFireCoolTime <= 0)
	{
		Fire();
		isFireCoolTime = kFireCoolTime;
	}*/
	worldTransform_.translation_ += approachVelocity_;
	if (worldTransform_.translation_.z < 0.0f)
	{
		phase_ = Phase::Leave;
	}
}

void Enemy::LeaveMove()
{
	worldTransform_.translation_ += leaveVelocity_;
}

void Enemy::Fire()
{
	EnemyBullet* newBullet = new EnemyBullet();

	newBullet->Initialize(model_, worldTransform_.translation_);
	bullets_.push_back(newBullet);
}

void Enemy::FireReset()
{
	Fire();
	timedCalls_.push_back(new TimedCall(std::bind(&Enemy::FireReset, this), kFireCoolTime));
}



void(Enemy::* Enemy::spFuncTable[])() = {
	&Enemy::ApproachMove,
	&Enemy::LeaveMove
};
