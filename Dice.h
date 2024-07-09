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
	void InitVertexData() override;
	void InitIndexData() override;
};

