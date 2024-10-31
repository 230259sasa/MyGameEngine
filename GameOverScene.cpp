#include "GameOverScene.h"
#include"Engine\SceneManager.h"
#include"Engine\Input.h"

GameOverScene::GameOverScene(GameObject* parent)
	:GameObject(parent, "GameOverScene")
{
}

void GameOverScene::Initialize()
{
	tex = new Sprite();
	tex->Load("Assets\\GameOver.png");
}

void GameOverScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		if (pSM != nullptr)
			pSM->ChangeScene(SCENE_ID_TITLE);
	}
}

void GameOverScene::Draw()
{
	tex->Draw(transform_);
}

void GameOverScene::Release()
{
}
