#include "PlayScene.h"
#include"Player.h"
#include"Enemy.h"
PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	/*Player* pPlayer;
	pPlayer = new Player(this);
	pPlayer->Initialize();
	childList_.push_back(pPlayer);*/

	Instantiate<Enemy>(this);
	Instantiate<Player>(this);
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
