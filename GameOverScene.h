#pragma once
#include "Engine\GameObject.h"
#include"Engine\Sprite.h"

class GameOverScene :
    public GameObject
{
    Sprite* tex;
public:
    GameOverScene(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

