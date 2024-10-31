#pragma once
#include"Engine/GameObject.h"
#include"Engine/Sprite.h"

class PlayScene :
    public GameObject
{
	Sprite* tex;
public:
	PlayScene(GameObject* parent);
	~PlayScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

