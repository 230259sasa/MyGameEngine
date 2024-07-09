#pragma once
#include "Direct3D.h"
#include<fbxsdk.h>
#include <DirectXMath.h>
#include "Texture.h"
#include<vector>
#include"Transform.h"
#include<filesystem>

#pragma comment(lib, "LibFbxSDK-MT.lib")
#pragma comment(lib, "LibXml2-MT.lib")
#pragma comment(lib, "zlib-MT.lib")

class FBX
{
	//コンスタントバッファー:　アプリ側から、シェーダーに毎フレーム渡したい情報
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;
		XMMATRIX	matW;
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;
		//XMVECTOR uv;
		//XMVECTOR normal; //ノーマル追加（法線ベクトル）
	};

	ID3D11Buffer* pVertexBuffer_;//頂点バッファ用メモリ
	ID3D11Buffer* pIndexBuffer_;//インデックスバッファ用メモリ
	ID3D11Buffer* pConstantBuffer_;//コンスタントバッファ用メモリ
	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
public:
	FBX();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
};

