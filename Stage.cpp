#include "Stage.h"
#include"Fbx.h"
#include"Input.h"
#include"Camera.h"
//#include "Direct3D.cpp"

Stage::Stage()
{
}

Stage::~Stage()
{
}

void Stage::Initialize()
{
	std::string path[5] = { "BoxDefault" , "BoxBrick" , "BoxSand" , "BoxWater" , "BoxGrass" };
	for (int i = 0; i < 5; i++) {
		pFbx[i] = new FBX;
		pFbx[i]->Load("Assets/" + path[i] + ".fbx");
	}

	for (int i = 0; i < 20; i++) {
		for (int z = 0; z < 20; z++) {
			table[i][z].height = 1;
			table[i][z].type = 0;
		}
	}
	table[0][0].height = 5;
	table[0][0].type = 2;
	table[3][3].height = 2;
	table[10][1].height = 3;

	table[3][3].type = 1;
	table[10][1].type = 4;
}

void Stage::Update()
{
	if (Input::IsMouseButtonDown(0)) 
	{
		XMMATRIX matView = Camera::GetViewMatrix();
		XMMATRIX matProj = Camera::GetProjectionMatrix();

		//float w = Direct3D::WINDOW_WIDTH / 2;
		//float h = Direct3D::WINDOW_HEIGHT / 2;
		float w = 800 / 2;
		float h = 600 / 2;

		XMMATRIX vp =
		{
			w, 0, 0, 0,
			0,-h, 0, 0,
			0, 0, 1, 0,
			w, h, 0, 1
		};

		XMMATRIX invView = XMMatrixInverse(nullptr, matView);
		XMMATRIX invProj = XMMatrixInverse(nullptr, matProj);
		XMMATRIX invVP = XMMatrixInverse(nullptr, vp);

		////////////////////
		//XMFLOAT3 mousePos = Input::GetMousePosition();
		/*XMFLOAT3 mousePos;
		XMStoreFloat3(&mousePos, Input::GetMousePosition());
		mousePos.z = 0;
		XMVECTOR mouseFrontPos = XMLoadFloat3(&mousePos);*/
		/////////////////
		XMVECTOR mouseFrontPos = Input::GetMousePosition();
		XMFLOAT3 mousePos;
		XMStoreFloat3(&mousePos, mouseFrontPos);
		mousePos.z = 0;
		mouseFrontPos = XMLoadFloat3(&mousePos);
		///////////

		mousePos.z = 1;
		XMVECTOR mouseBackPos = XMLoadFloat3(&mousePos);

		mouseFrontPos = XMVector3TransformCoord(mouseFrontPos, invVP * invProj * invView);
		mouseBackPos = XMVector3TransformCoord(mouseBackPos, invVP * invProj * invView);


		RayCastData data;
		XMStoreFloat4(&data.start,mouseFrontPos);
		XMStoreFloat4(&data.dir,mouseBackPos-mouseFrontPos);

		Transform trans;
		for (int x = 0; x < 20; x++) {
			for (int z = 0; z < 20; z++) {
				for (int y = 0; y < table[x][z].height; y++) {
					trans.position_.x = -x;
					trans.position_.y = y;
					trans.position_.z = -z;

					//種類ごとに　　　　　　ブロックの位置をいれる（trans
					pFbx[table[x][z].type]->RayCast(data, trans);

					if (data.hit == true) {
						table[x][z].height++;
						//いずれ総当たりで当たった距離が一番小さいブロックのみを操作する
						return;
					}
				}
			}
		}
	}

}

void Stage::Draw()
{
	Transform t;
	for (int x = 0; x < 20; x++) {
		for (int z = 0; z < 20; z++) {
			for (int y = 0; y < table[x][z].height; y++) {
				t.position_.x = -x;
				t.position_.y = y;
				t.position_.z = -z;
				int type = table[x][z].type;
				pFbx[type]->Draw(t);
			}
		}
	}
}

void Stage::Release()
{
	//pFbx->Release();
	//SAFE_DELETE(pFbx);
	for (int i = 0; i < 5; i++) {
		pFbx[i]->Release();
		SAFE_DELETE(pFbx[i]);
	}
}
