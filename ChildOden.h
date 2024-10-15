#pragma once
#include "Engine\GameObject.h"

class FBX;

class ChildOden :
	public GameObject
{
	//FBX* pOden;
	int hModel;
public:
	ChildOden(GameObject* parent);
	~ChildOden();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

