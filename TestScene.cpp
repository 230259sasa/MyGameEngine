#include "TestScene.h"
#include"Engine/Input.h"
#include"Engine\SceneManager.h"

TestScene::TestScene(GameObject* parent)
	:GameObject(parent,"TestScene")
{
}

void TestScene::Initialize()
{
	tex = new Sprite();
	tex->Load("Assets\\FLY_BARD.png");
	transform_.scale_ = { 0.2,0.2,0.2 };   
}

void TestScene::Update()
{
	if (Input::IsKeyDown(DIK_SPACE)) {
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		if (pSM != nullptr)
		pSM->ChangeScene(SCENE_ID_PLAY);
	}
}

void TestScene::Draw()
{
	tex->Draw(transform_);
}

void TestScene::Release()
{
}
