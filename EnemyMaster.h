#pragma once
#include "Engine\GameObject.h"
#include<vector>

class EnemyMaster :
	public GameObject
{
	float eTimer;
	int eColumn;
	std::vector<std::vector<int>> enemys;
	enum EnemyType {
		NONE=0,
		NORMAL
	};
public:
	EnemyMaster(GameObject* parent);
	~EnemyMaster();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

