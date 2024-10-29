#include "Player.h"
#include"Engine/FBX.h"
#include"ChildOden.h"
#include"Engine/Input.h"
#include"Engine/Model.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"), hModel(-1)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	hModel = Model::Load("Assets/oden.fbx");
	transform_.position_.y = -4;
}

void Player::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		GameObject* pCo = Instantiate<ChildOden>(this);
		if(pCo != nullptr)
		pCo->SetPosition(transform_.position_);
	}
	if (Input::IsKey(DIK_LEFT)) {
		transform_.position_.x -= 0.1;
	}
	if (Input::IsKey(DIK_RIGHT)) {
		transform_.position_.x += 0.1;
	}
}

void Player::Draw()
{
	Model::SetTransform(hModel,transform_);
	Model::Draw(hModel);
}

void Player::Release()
{
	//pFbx->Release();
	//delete pFbx;
}
