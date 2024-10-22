#include "Enemy.h"
#include"Engine\Model.h"

Enemy::Enemy(GameObject* parent)
	:GameObject(parent,"Enemy")
{
}

Enemy::~Enemy()
{
}

void Enemy::Initialize()
{
	transform_.position_.y = 3;

	hModel = Model::Load("Assets\\BoxDefault.fbx");
}

void Enemy::Update()
{
	static int dt;
	dt += 10;

	float nTime = dt / (60.0f * 10.0f) - 2.0f;
	float sn = sin(nTime);
	transform_.position_.x = 4.0f * sn;
}

void Enemy::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Enemy::Release()
{
}
