#include "Player.h"
#include"Engine\FBX.h"
#include"ChildOden.h"
#include"Engine\Input.h"

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),pOden(nullptr)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	pOden = new FBX;
	pOden->Load("Assets\\oden.fbx");
	GameObject* pCo = Instantiate<ChildOden>(this);
	pCo->SetPosition(0,0,-1);
}

void Player::Update()
{
	transform_.rotate_.y += 1;
	if (Input::IsKeyDown(DIK_SPACE)) {
		KillMe();
	}
}

void Player::Draw()
{
	pOden->Draw(transform_);
}

void Player::Release()
{
	pOden->Release();
	delete pOden;
}
