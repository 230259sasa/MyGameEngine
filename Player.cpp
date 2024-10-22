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
	Instantiate<ChildOden>(this);
}

void Player::Update()
{
	//transform_.rotate_.y += 1;
	if (Input::IsKeyDown(DIK_SPACE)) {
		ChildOden* pCO = Instantiate<ChildOden>(this);
		pCO->SetPosition(transform_.position_);
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
