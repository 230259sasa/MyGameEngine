#include "EnemyMaster.h"
#include"Enemy.h"
#include"Engine/SceneManager.h"

namespace EnemyMasterSetting {
	const int WEIDTH_ENEMYS = 6;
	const int HEIGHT_ENEMYS = 4;
	const float ENEMY_SPAWN_PACE = 4.0f;
}

namespace EMS = EnemyMasterSetting;

EnemyMaster::EnemyMaster(GameObject* parent)
	:GameObject(parent,"EnemyMaster")
{
}

EnemyMaster::~EnemyMaster()
{
}

void EnemyMaster::Initialize()
{
	eColumn = 0;
	eTimer = 1.0f;
	for(int i=0;i<EMS::HEIGHT_ENEMYS;i++){
		std::vector<int> v;
		for (int j = 0; j < EMS::WEIDTH_ENEMYS; j++) {
			v.push_back(rand()%2);
		}
		enemys.push_back(v);
	}
}

void EnemyMaster::Update()
{
	eTimer -= 1.0f / 60.0f;
	if (eTimer <= 0 && eColumn < EMS::HEIGHT_ENEMYS) {
		for (int i = 0; i < EMS::WEIDTH_ENEMYS; i++) {
			if (enemys[eColumn][i] == 1) {
				Enemy* e = Instantiate<Enemy>(FindObject("PlayScene"));
				e->SetPosition({ -6.5f + i * 2.5f,5,0 });
			}
		}
		eColumn++;
		eTimer = EMS::ENEMY_SPAWN_PACE;
	}

	if (eColumn >= EMS::HEIGHT_ENEMYS && GetRootJob()->FindChildObjectList("Enemy").size() <= 0) {
   		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		if (pSM != nullptr)
			pSM->ChangeScene(SCENE_ID_CLEAR);
	}
}

void EnemyMaster::Draw()
{
}

void EnemyMaster::Release()
{
}
