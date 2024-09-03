#pragma once
#include"Transform.h"

class Controller
{
	Transform transform;
public:
	Controller();

	~Controller();
    //初期化
    void Initialize();

    //更新
    void Update();

    //描画
    void Draw();

    //開放
    void Release();
};

