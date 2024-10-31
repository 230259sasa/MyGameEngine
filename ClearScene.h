#pragma once
#include "Engine\GameObject.h"
#include"Engine\Sprite.h"

class ClearScene :
    public GameObject
{
    Sprite* tex;
public:
    ClearScene(GameObject* parent);
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;
};

