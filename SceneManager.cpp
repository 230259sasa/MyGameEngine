#include "SceneManager.h"
#include"TestScene.h"

SceneManager::SceneManager(GameObject* parent)
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
}

void SceneManager::Draw()
{
}

void SceneManager::Release()
{
}
