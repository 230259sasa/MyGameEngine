#include "Stage.h"
#include"Fbx.h"
#include"Input.h"
#include"Camera.h"
#include"resource.h"
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

	selectMode = 0;
	selectType = 0;
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
						if (selectMode == SELECT_MODE::Up) {
							table[x][z].height++;
						}
						else if (selectMode == SELECT_MODE::Down) {
							table[x][z].height += (table[x][z].height == 1) ? 0 : -1;
						}
						else if (selectMode == SELECT_MODE::Change) {
							table[x][z].type = selectType;
						}
						
						//いずれ総当たりで当たった距離が一番小さいブロックのみを操作する
						//data.distが距離
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

BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		//HWND h = GetDlgItem(hDlg,IDC_RADIO_UP);
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hDlg, IDC_COMBO), CB_ADDSTRING, 0, (LPARAM)L"デフォルト");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO), CB_ADDSTRING, 0, (LPARAM)L"レンガ");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO), CB_ADDSTRING, 0, (LPARAM)L"草");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO), CB_ADDSTRING, 0, (LPARAM)L"砂");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO), CB_ADDSTRING, 0, (LPARAM)L"水");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO), CB_SETCURSEL, 0, 0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wp)) {
		case IDC_RADIO_UP:
			selectMode = 0;
			break;
		case IDC_RADIO_DOWN:
			selectMode = 1;
			break;
		case IDC_RADIO_CHANGE:
			selectMode = 2;
			break;
		case ID_MENU_NEW:
			break;
		case ID_MENU_OPEN:
			break;
		case ID_MENU_SAVE:
			break;
		case IDC_COMBO:
			selectType = (int)SendMessage(GetDlgItem(hDlg, IDC_COMBO), CB_GETCURSEL,0,0);
			break;
		}
		break;
	}
	return FALSE;
}