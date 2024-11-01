#include "PlayScene.h"
#include"Player.h"
#include"Enemy.h"
#include"Engine\Model.h"
#include"Engine\Camera.h"
#include"EnemyMaster.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	/*Instantiate<Enemy>(this);
	Enemy* e = Instantiate<Enemy>(this);
	e->SetPosition(3, 0, 0);*/
	Instantiate<Player>(this);
	Instantiate<EnemyMaster>(this);
	Camera::SetPosition({ 0,0,-15 });
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{
}

void PlayScene::Release()
{
}
