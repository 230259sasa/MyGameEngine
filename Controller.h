#pragma once
#include"Transform.h"

class Controller
{
	Transform transform;
public:
	Controller();

	~Controller();
    //������
    void Initialize();

    //�X�V
    void Update();

    //�`��
    void Draw();

    //�J��
    void Release();
};

