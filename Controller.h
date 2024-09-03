#pragma once
#include"Transform.h"

class Controller
{
	Transform transform;
public:
	Controller();

	~Controller();
    //‰Šú‰»
    void Initialize();

    //XV
    void Update();

    //•`‰æ
    void Draw();

    //ŠJ•ú
    void Release();
};

