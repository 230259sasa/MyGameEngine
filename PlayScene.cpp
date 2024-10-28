#include "PlayScene.h"
#include"Player.h"
#include"Enemy.h"
#include"Engine\Model.h"
#include"Engine\Camera.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Initialize()
{
	Model::Load("Assets\\oden.fbx");
	Model::Load("Assets\\BoxDefault.fbx");
	Model::Load("Assets\\oden.fbx");
	Instantiate<Enemy>(this);
	Instantiate<Player>(this);
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
