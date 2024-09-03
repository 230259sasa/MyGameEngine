#include "Stage.h"
#include"Fbx.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	pFbx = new FBX;
	pFbx->Load("Assets/BoxDefault.fbx");
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Transform t;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			t.position_.x = i;
			t.position_.z = -j;
			pFbx->Draw(t);
		}
	}
}

void Stage::Release()
{
	pFbx->Release();
	SAFE_DELETE(pFbx);
}
