#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>
#include "Texture.h"
#include<vector>

using namespace DirectX;

//コンスタントバッファー:　アプリ側から、シェーダーに毎フレーム渡したい情報
struct CONSTANT_BUFFER
{
	XMMATRIX	matW;
};

//XMFLOAT3でもよい。
//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};


class Sprite
{
private:
	uint64_t vertexNum_;//頂点数
	std::vector<VERTEX> vertices_;//頂点情報
	uint64_t indexNum_;//インデックス数
	std::vector<int> indices_;//インデックス情報
	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;    //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ

	Texture* pTexture_;
public:
	Sprite();
	~Sprite();
	HRESULT Initialize();
	virtual void Draw(XMMATRIX& worldMatrix);
	void Release();
private:
	void InitVertexData();
	HRESULT CreateVertexBuffer();

	void InitIndexData();
	HRESULT CreateIndexBuffer();

	HRESULT CreateConstantBuffer();

	HRESULT LoadTexture();
	void PassDataToCB(DirectX::XMMATRIX& worldMatrix);
	void SetBufferToPipeline();
};

