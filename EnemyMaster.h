#pragma once
#include "Engine\GameObject.h"

namespace EnemyMasterSetting {
	const int WEIDTH_ENEMYS = 6;
	const int HEIGHT_ENEMYS = 20;
}

class EnemyMaster :
	public GameObject
{
	enum EnemyType {
		NONE=0,
		NORMAL
	};
public:
	EnemyMaster();
	~EnemyMaster();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;
};

