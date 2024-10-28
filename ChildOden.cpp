#include "ChildOden.h"
#include"Engine\FBX.h"
#include"Engine/Model.h"
#include"Enemy.h"
#include"Engine\SphereCollider.h"

ChildOden::ChildOden(GameObject* parent) :
	GameObject(parent, "child"), hModel(-1)
{
}

ChildOden::~ChildOden()
{
}

void ChildOden::Initialize()
{
	/*pOden = new FBX;
	pOden->Load("Assets\\oden.fbx");*/
	hModel = Model::Load("Assets\\oden.fbx");
	transform_.scale_.x = 0.4f;
	transform_.scale_.y = 0.4f;
	transform_.scale_.z = 0.4f;
	transform_.position_.x = 1.0f;
	transform_.position_.y = 1.0f;

	SphereCollider* col = new SphereCollider(0.5);
	AddCollider(col);
}

void ChildOden::Update()
{
	transform_.position_.y += 0.05;
	//transform_.rotate_.y++;
	if (transform_.position_.y > 4) {
		KillMe();
	}

	Enemy* enemy = (Enemy*)FindObject("Enemy");
	if (enemy == nullptr) { return; }
	Collision(enemy);
}

void ChildOden::Draw()
{
	//pOden->Draw(transform_);
	Model::SetTransform(hModel,transform_);
	Model::Draw(hModel);
}

void ChildOden::Release()
{
}

void ChildOden::OnCollision(GameObject* pTarget)
{
	KillMe();
	pTarget->KillMe();
}
