#include "ChildOden.h"
#include"Engine\FBX.h"

ChildOden::ChildOden(GameObject* parent) :
	GameObject(parent, "child"), pOden(nullptr)
{
}

ChildOden::~ChildOden()
{
}

void ChildOden::Initialize()
{
	pOden = new FBX;
	pOden->Load("Assets\\oden.fbx");
	transform_.scale_.x = 0.4f;
	transform_.scale_.y = 0.4f;
	transform_.scale_.z = 0.4f;
	transform_.position_.x = 1.0f;
	transform_.position_.y = 1.0f;
}

void ChildOden::Update()
{
	//transform_.rotate_.y++;
}

void ChildOden::Draw()
{
	pOden->Draw(transform_);
}

void ChildOden::Release()
{
}
