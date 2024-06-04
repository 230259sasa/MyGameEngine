//インクルード
#include <Windows.h>
#include<tchar.h>
#include <Windows.h>
#include "Direct3D.h"
#include"Quad.h"
#include"Camera.h"

// MicroSoft Disk Operating System
// ハイレベルシェーダ
//プロトタイプ宣言

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

const wchar_t* WIN_CLASS_NAME = L"SampleGame";
const wchar_t* APP_NAME = L"サンプルゲーム";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

//エントリーポイント
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);             //この構造体のサイズ
	wc.hInstance = hInstance;                   //インスタンスハンドル
	wc.lpszClassName = L"SampleGame";            //ウィンドウクラス名
	wc.lpfnWndProc = WndProc;                   //ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;         //スタイル（デフォルト）
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //アイコン
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO);   //小さいアイコン
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);   //マウスカーソル
	wc.lpszMenuName = NULL;                     //メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //背景（白）
	RegisterClassEx(&wc); //クラスを登録

	//ウィンドウサイズの計算
	RECT winRect = { 0,0,WINDOW_WIDTH,WINDOW_HEIGHT };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
	int winW = winRect.right - winRect.left;
	int winH = winRect.bottom - winRect.top;

	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,		 //ウィンドウクラス名
		APP_NAME,			 //タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW, //スタイル（普通のウィンドウ）
		CW_USEDEFAULT,       //表示位置左（おまかせ）
		CW_USEDEFAULT,       //表示位置上（おまかせ）
		WINDOW_WIDTH,                 //ウィンドウ幅
		WINDOW_HEIGHT,                 //ウィンドウ高さ
		NULL,                //親ウインドウ（なし）
		NULL,                //メニュー（なし）
		hInstance,           //インスタンス
		NULL                 //パラメータ（なし）
	);

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	//Direct3D初期化
	HRESULT hr = Direct3D::Initialize(winW, winH, hWnd);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Direct3Dの初期化に失敗", NULL, MB_OK);
		return 0;
	}

	//Camera初期化
	Camera::Initialize();

	Quad* q;
	q = new Quad();
	hr = q->Initialize();
	if (FAILED(hr))
	{
		MessageBox(NULL, L"Quadの生成に失敗", NULL, MB_OK);
		return 0;
	}
	q->Initialize();

	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし
		else
		{
			//ゲームの処理

			Direct3D::BeginDraw();

			//Cameraの更新
			Camera::Update();

			//自前の描画処理をここに追加
			XMMATRIX mat = XMMatrixRotationY(XMConvertToRadians(45));
			q->Draw(mat);

			//描画処理

			Direct3D::EndDraw();
		}
	}

	SAFE_DELETE(q);
	Direct3D::Release();
	return 0;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);  //プログラム終了
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}