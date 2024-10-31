#include "ClearScene.h"
#include"Engine\SceneManager.h"
#include"Engine\Input.h"

ClearScene::ClearScene(GameObject* parent)
	:GameObject(parent, "ClearScene")
{
}

void ClearScene::Initialize()
{
	tex = new Sprite();
	tex->Load("Assets\\Clear.png");
}

void ClearScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		if (pSM != nullptr)
			pSM->ChangeScene(SCENE_ID_TITLE);
	}
}

void ClearScene::Draw()
{
	tex->Draw(transform_);
}

void ClearScene::Release()
{
}
