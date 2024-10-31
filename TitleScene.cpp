#include "TitleScene.h"
#include"Engine\SceneManager.h"
#include"Engine\Input.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent, "TitleScene")
{
}

void TitleScene::Initialize()
{
	tex = new Sprite();
	tex->Load("Assets\\Title.png");
}

void TitleScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		if (pSM != nullptr)
			pSM->ChangeScene(SCENE_ID_PLAY);
	}
}

void TitleScene::Draw()
{
	tex->Draw(transform_);
}

void TitleScene::Release()
{
}
