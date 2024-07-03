#pragma once
#include "Quad.h"
#include"Transform.h"

class Dice :
    public Quad
{

public:
	Dice() :Quad() {}//親のコンストラクタを呼ぶ
	~Dice();
	HRESULT Initialize() override;
	//virtual void Draw(Transform& transform);
	void InitVertexData() override;
	void InitIndexData() override;
};

