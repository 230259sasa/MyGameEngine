#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>
#include "Texture.h"
#include<vector>

using namespace DirectX;

//�R���X�^���g�o�b�t�@�[:�@�A�v��������A�V�F�[�_�[�ɖ��t���[���n���������
struct CONSTANT_BUFFER
{
	XMMATRIX	matW;
};

//XMFLOAT3�ł��悢�B
//���_���
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
};


class Sprite
{
private:
	uint64_t vertexNum_;//���_��
	std::vector<VERTEX> vertices_;//���_���
	uint64_t indexNum_;//�C���f�b�N�X��
	std::vector<int> indices_;//�C���f�b�N�X���
	ID3D11Buffer* pVertexBuffer_;	//���_�o�b�t�@
	ID3D11Buffer* pIndexBuffer_;    //�C���f�b�N�X�o�b�t�@
	ID3D11Buffer* pConstantBuffer_;	//�R���X�^���g�o�b�t�@

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

