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

					//��ނ��ƂɁ@�@�@�@�@�@�u���b�N�̈ʒu�������itrans
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
						
						//�����ꑍ������œ���������������ԏ������u���b�N�݂̂𑀍삷��
						//data.dist������
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

void Stage::Save()
{
	WCHAR fileName[MAX_PATH] = L"����.map";  //�t�@�C����������ϐ�

	//�u�t�@�C����ۑ��v�_�C�A���O�̐ݒ�
	OPENFILENAME ofn;                         	//���O�����ĕۑ��_�C�A���O�̐ݒ�p�\����
	ZeroMemory(&ofn, sizeof(ofn));            	//�\���̏�����
	ofn.lStructSize = sizeof(OPENFILENAME);   	//�\���̂̃T�C�Y
	ofn.lpstrFilter =	TEXT("�}�b�v�f�[�^(*.map)\0*.map\0")        //�����t�@�C���̎��
						TEXT("�e�L�X�g�f�[�^(*.txt)\0*.txt\0")
						TEXT("���ׂẴt�@�C��(*.*)\0*.*\0\0");     //����
	ofn.lpstrFile = fileName;               	//�t�@�C����
	ofn.nMaxFile = MAX_PATH;               	//�p�X�̍ő啶����
	ofn.Flags = OFN_OVERWRITEPROMPT;   		//�t���O�i�����t�@�C�������݂�����㏑���m�F�j
	ofn.lpstrDefExt = L"map";                  	//�f�t�H���g�g���q

	//�u�t�@�C����ۑ��v�_�C�A���O
	BOOL selFile;
	selFile = GetSaveFileName(&ofn);

	//�L�����Z�������璆�f
	if (selFile == FALSE) return;



	HANDLE hFile;        //�t�@�C���̃n���h��
	hFile = CreateFile(
		fileName,                 //�t�@�C����
		GENERIC_WRITE,           //�A�N�Z�X���[�h�i�������ݗp�j
		0,                      //���L�i�Ȃ��j
		NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
		CREATE_ALWAYS,           //�쐬���@
		FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
		NULL);                  //�g�������i�Ȃ��j

	DWORD dwBytes = 0;  //�������݈ʒu
	WriteFile(
		hFile,                   //�t�@�C���n���h��
		"LC",                  //�ۑ�����f�[�^�i������j
		(DWORD)strlen("LC"),   //�������ޕ�����
		&dwBytes,                //�������񂾃T�C�Y������ϐ�
		NULL);                   //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j

	CloseHandle(hFile);
}

void Stage::Open()
{
	HANDLE hFile;        //�t�@�C���̃n���h��
	hFile = CreateFile(
		L"test.txt",                 //�t�@�C����
		GENERIC_READ,           //�A�N�Z�X���[�h�i�ǂݍ��ݗp�j
		0,                      //���L�i�Ȃ��j
		NULL,                   //�Z�L�����e�B�����i�p�����Ȃ��j
		OPEN_EXISTING,           //�쐬���@
		FILE_ATTRIBUTE_NORMAL,  //�����ƃt���O�i�ݒ�Ȃ��j
		NULL);                  //�g�������i�Ȃ��j

	//�t�@�C���̃T�C�Y���擾
	DWORD fileSize = GetFileSize(hFile, NULL);

	//�t�@�C���̃T�C�Y�����������m��
	char* data;
	data = new char[fileSize];

	DWORD dwBytes = 0; //�ǂݍ��݈ʒu

	ReadFile(
		hFile,     //�t�@�C���n���h��
		data,      //�f�[�^������ϐ�
		fileSize,  //�ǂݍ��ރT�C�Y
		&dwBytes,  //�ǂݍ��񂾃T�C�Y
		NULL);     //�I�[�o�[���b�v�h�\���́i����͎g��Ȃ��j

	CloseHandle(hFile);
}

LRESULT Stage::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
		Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);  //�v���O�����I��
		return 0; 
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_MENU_NEW:
			break;
		case ID_MENU_OPEN:
			Open();
			break;
		case ID_MENU_SAVE:
			Save();
			break;
		}
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

BOOL Stage::DialogProc(HWND hDlg, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_INITDIALOG:
		//HWND h = GetDlgItem(hDlg,IDC_RADIO_UP);
		SendMessage(GetDlgItem(hDlg, IDC_RADIO_UP), BM_SETCHECK, BST_CHECKED, 0);
		SendMessage(GetDlgItem(hDlg, IDC_COMBO), CB_ADDSTRING, 0, (LPARAM)L"�f�t�H���g");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO), CB_ADDSTRING, 0, (LPARAM)L"�����K");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO), CB_ADDSTRING, 0, (LPARAM)L"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO), CB_ADDSTRING, 0, (LPARAM)L"��");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO), CB_ADDSTRING, 0, (LPARAM)L"��");
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
		case IDC_COMBO:
			selectType = (int)SendMessage(GetDlgItem(hDlg, IDC_COMBO), CB_GETCURSEL,0,0);
			break;
		}
		break;
	}
	return FALSE;
}