#include "Enemy.h"
#include"Engine\Model.h"
#include"Engine\SphereCollider.h"

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
	dtime = 0;
	hModel = Model::Load("Assets\\BoxDefault.fbx");
	SphereCollider* col = new SphereCollider(0.5);
	AddCollider(col);
}

void Enemy::Update()
{
	dtime += 10;

	float nTime = dtime / (60.0f * 15.0f) - 2.0f;
	float sn = sin(nTime);
	transform_.position_.x = 8.0f * sn;
}

void Enemy::Draw()
{
	Model::SetTransform(hModel, transform_);
	Model::Draw(hModel);
}

void Enemy::Release()
{
}
