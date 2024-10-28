#include "SceneManager.h"
#include"../TestScene.h"
#include"../PlayScene.h"

SceneManager::SceneManager(GameObject* parent)
	:GameObject(parent,"SceneManager")
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::Initialize()
{
	currentSceneID_ = SCENE_ID_TEST;
	nextSceneID_ = currentSceneID_;
	Instantiate<TestScene>(this);
}

void SceneManager::Update()
{
	if (nextSceneID_ != currentSceneID_) {
		switch (nextSceneID_) {
		case SCENE_ID_PLAY:
			Instantiate<PlayScene>(this);break;
		case SCENE_ID_TEST:
			Instantiate<TestScene>(this);break;
		default:break;
		}
		currentSceneID_ = nextSceneID_;
	}
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}
