#include "Quad.h"
#include "Camera.h"

Quad::Quad()
	:pTexture_(nullptr),pVertexBuffer_(nullptr),pIndexBuffer_(nullptr),pConstantBuffer_(nullptr)
{
}

Quad::~Quad()
{
}

HRESULT Quad::Initialize()
{
	HRESULT hr;
	// 頂点情報
	//VERTEX vertices[] =
	//{
	//	{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0, 0.0, 0.0, 0.0)},	// 四角形の頂点（左上
	//	{ XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0, 0.0, 0.0, 0.0)},	// 四角形の頂点（右上）, UV
	//	{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(1.0, 1.0, 0.0, 0.0)},	// 四角形の頂点（右下）, UV
	//	{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0, 1.0, 0.0, 0.0)}	// 四角形の頂点（左下）, UV
	//};

	VERTEX vertices[] =
	{
		//正面　１
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0, 0.0, 0.0, 0.0)},	// 四角形の頂点（左上
		{ XMVectorSet( 1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25, 0.0, 0.0, 0.0)},	// 四角形の頂点（右上）, UV
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(0.25, 0.5, 0.0, 0.0)},	// 四角形の頂点（右下）, UV
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.0, 0.5, 0.0, 0.0)},	// 四角形の頂点（左下）, UV
		//後ろ　6
		{ XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.25, 0.5, 0.0, 0.0)},	// 四角形の頂点（左上
		{ XMVectorSet(1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.5, 0.5, 0.0, 0.0)},	// 四角形の頂点（右上）, UV
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),  XMVectorSet(0.5, 1.0, 0.0, 0.0)},	// 四角形の頂点（右下）, UV
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.25, 1.0, 0.0, 0.0)},	// 四角形の頂点（左下）, UV
		//migi 3
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.5, 0.0, 0.0, 0.0)},	// 四角形の頂点（右上）, UV
		{ XMVectorSet(1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.75, 0.0, 0.0, 0.0)},	// 四角形の頂点（右oku上）, UV
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(0.5, 0.5, 0.0, 0.0)},	// 四角形の頂点（右下）, UV
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),  XMVectorSet(0.75, 0.5, 0.0, 0.0)},	// 四角形の頂点（右oku下）, UV
		//hidari 4
		{ XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.75, 0.0, 0.0, 0.0)},	// 四角形の頂点（左oku上
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(1.0, 0.0, 0.0, 0.0)},	// 四角形の頂点（左上
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(1.0, 0.5, 0.0, 0.0)},	// 四角形の頂点（左下）, UV
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.75, 0.5, 0.0, 0.0)},	// 四角形の頂点（左oku下）, UV
		//ue 5
		{ XMVectorSet(-1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.0, 0.5, 0.0, 0.0)},	// 四角形の頂点（左oku上
		{ XMVectorSet(1.0f,  1.0f, 2.0f, 0.0f), XMVectorSet(0.25, 0.5, 0.0, 0.0)},	// 四角形の頂点（右oku上）, UV
		{ XMVectorSet(1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.25, 1.0, 0.0, 0.0)},	// 四角形の頂点（右上）, UV
		{ XMVectorSet(-1.0f,  1.0f, 0.0f, 0.0f), XMVectorSet(0.0, 1.0, 0.0, 0.0)},	// 四角形の頂点（左上
		//sita 2
		{ XMVectorSet(-1.0f, -1.0f, 0.0f, 0.0f), XMVectorSet(0.25, 0.0, 0.0, 0.0)},	// 四角形の頂点（左下）, UV
		{ XMVectorSet(1.0f, -1.0f, 0.0f, 0.0f),  XMVectorSet(0.5, 0.0, 0.0, 0.0)},	// 四角形の頂点（右下）, UV
		{ XMVectorSet(1.0f, -1.0f, 2.0f, 0.0f),  XMVectorSet(0.5, 0.5, 0.0, 0.0)},	// 四角形の頂点（右oku下）, UV
		{ XMVectorSet(-1.0f, -1.0f, 2.0f, 0.0f), XMVectorSet(0.25, 0.5, 0.0, 0.0)},	// 四角形の頂点（左oku下）, UV
	};

	//インデックス情報
	int index[] = { 0,1,2, 0,2,3, 6,5,4, 7,6,4, 8,9,10, 11,10,9, 12,13,14, 12,14,15, 16,17,18, 16,18,19, 20,21,22, 20,22,23};
	
	// 頂点データ用バッファの設定
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(vertices);
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices;
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);

	if (FAILED(hr))
	{
		MessageBox(NULL, L"頂点バッファの作成に失敗", NULL, MB_OK);
		return hr;
	}

	// インデックスバッファを生成する
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(index);
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index;
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"インデックスバッファの作成に失敗", NULL, MB_OK);
		return hr;
	}

	//コンスタントバッファ作成
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;

	// コンスタントバッファの作成
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"コンスタントバッファの作成に失敗", NULL, MB_OK);
		return hr;
	}

	pTexture_ = new Texture;
	pTexture_->Load("Asset\\dice.png");

	return S_OK;
}

void Quad::Draw()
{
	//コンスタントバッファに渡す情報
	
	//XMVECTOR position = { 0, 3, -10, 0 };	//カメラの位置
	//XMVECTOR target = { 0, 0, 0, 0 };	//カメラの焦点
	//XMMATRIX view = XMMatrixLookAtLH(position, target, XMVectorSet(0, 1, 0, 0));	//ビュー行列
	//XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 800.0f / 600.0f, 0.1f, 100.0f);//射影行列
	//

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(Camera::GetViewMatrix() * Camera::GetProjectionMatrix()); //view*projをカメラからとってくる
	// 間違ってる？
	cb.matW =  Camera::GetProjectionMatrix();

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開
	
	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	Direct3D::pContext->DrawIndexed(36, 0, 0);
}

void Quad::Draw(XMMATRIX& worldMatrix)
{

	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(worldMatrix * Camera::GetViewMatrix() * Camera::GetProjectionMatrix()); //view*projをカメラからとってくる

	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPUからのデータアクセスを止める
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// データを値を送る
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//再開

	//頂点バッファ
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// インデックスバッファーをセット
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//コンスタントバッファ
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//頂点シェーダー用	
	Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//ピクセルシェーダー用

	//サンプラーとシェーダーリソースビューをシェーダにセット
	ID3D11SamplerState* pSampler = pTexture_->GetSampler();
	Direct3D::pContext->PSSetSamplers(0, 1, &pSampler);

	ID3D11ShaderResourceView* pSRV = pTexture_->GetSRV();
	Direct3D::pContext->PSSetShaderResources(0, 1, &pSRV);

	Direct3D::pContext->DrawIndexed(50, 0, 0);
}

void Quad::Release()
{
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}
