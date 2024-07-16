#include "FBX.h"
#include"Camera.h"

FBX::FBX()
    :pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr),
    vertexCount_(-1),polygonCount_(-1)
{
}

HRESULT FBX::Load(std::string fileName)
{
	//�}�l�[�W���𐶐�
	FbxManager* pFbxManager = FbxManager::Create();

	//�C���|�[�^�[�𐶐�
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//�V�[���I�u�W�F�N�g��FBX�t�@�C���̏��𗬂�����
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();
	
	//���b�V�������擾
	FbxNode* rootNode = pFbxScene->GetRootNode();
	FbxNode* pNode = rootNode->GetChild(0);
	FbxMesh* mesh = pNode->GetMesh();

	//�e���̌����擾
	vertexCount_ = mesh->GetControlPointsCount();	//���_�̐�
	polygonCount_ = mesh->GetPolygonCount();	//�|���S���̐�
	materialCount_ = pNode->GetMaterialCount();

	InitVertex(mesh);		//���_�o�b�t�@����
	InitIndex(mesh);
	InitConstantBuffer();
	InitMaterial(pNode);

	//�}�l�[�W�����
	pFbxManager->Destroy();
	return S_OK;
}

void FBX::InitVertex(fbxsdk::FbxMesh* mesh)
{
	//���_��������z��
	//VERTEX* vertices = new VERTEX[vertexCount_];
	std::vector<VERTEX> vertices(vertexCount_);

	//�S�|���S��
	for (DWORD poly = 0; poly < polygonCount_; poly++)
	{
		//3���_��
		for (int vertex = 0; vertex < 3; vertex++)
		{
			//���ׂ钸�_�̔ԍ�
			int index = mesh->GetPolygonVertex(poly, vertex);

			//���_�̈ʒu
			FbxVector4 pos = mesh->GetControlPointAt(index);
			vertices[index].position = XMVectorSet((float)pos[0], (float)pos[1], (float)pos[2], 0.0f);
		}
	}
	// ���_�o�b�t�@�쐬
	// ���_�f�[�^�p�o�b�t�@�̐ݒ�
	HRESULT hr;
	D3D11_BUFFER_DESC bd_vertex;
	bd_vertex.ByteWidth = sizeof(VERTEX) * vertices.size();
	bd_vertex.Usage = D3D11_USAGE_DEFAULT;
	bd_vertex.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd_vertex.CPUAccessFlags = 0;
	bd_vertex.MiscFlags = 0;
	bd_vertex.StructureByteStride = 0;
	D3D11_SUBRESOURCE_DATA data_vertex;
	data_vertex.pSysMem = vertices.data();
	hr = Direct3D::pDevice->CreateBuffer(&bd_vertex, &data_vertex, &pVertexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"���_�o�b�t�@�̍쐬�Ɏ��s", NULL, MB_OK);
	}
}

void FBX::InitIndex(fbxsdk::FbxMesh* mesh)
{
	//int* index = new int[polygonCount_ * 3];
	std::vector<int> index(polygonCount_ * 3);
	int count = 0;

	//�S�|���S��
	for (DWORD poly = 0; poly < polygonCount_; poly++)
	{
		//3���_��
		for (DWORD vertex = 0; vertex < 3; vertex++)
		{
			index[count] = mesh->GetPolygonVertex(poly, vertex);
			count++;
		}
	}
	HRESULT hr;
	D3D11_BUFFER_DESC   bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(int) * index.size();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = index.data();
	InitData.SysMemPitch = 0;
	InitData.SysMemSlicePitch = 0;
	hr = Direct3D::pDevice->CreateBuffer(&bd, &InitData, &pIndexBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"�C���f�b�N�X�o�b�t�@�̍쐬�Ɏ��s", NULL, MB_OK);
	}
	indexNum_ = index.size();
}

void FBX::InitConstantBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC cb;
	cb.ByteWidth = sizeof(CONSTANT_BUFFER);
	cb.Usage = D3D11_USAGE_DYNAMIC;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cb.MiscFlags = 0;
	cb.StructureByteStride = 0;
	hr = Direct3D::pDevice->CreateBuffer(&cb, nullptr, &pConstantBuffer_);
	if (FAILED(hr))
	{
		MessageBox(NULL, L"�R���X�^���g�o�b�t�@�̍쐬�Ɏ��s", NULL, MB_OK);
	}
}

void FBX::PassDataToCB(Transform& transform)
{
	CONSTANT_BUFFER cb;
	cb.matWVP = XMMatrixTranspose(transform.GetWorldMatrix() * Camera::GetViewMatrix() * Camera::GetProjectionMatrix());
	cb.matNormal = XMMatrixTranspose(transform.GetNormalMatrix()); //MATRIX�̊|���Z�̂�����DirectX�ƈႤ�̂œ]�u���Ƃ�i�Ȃ񂻂�j
	D3D11_MAPPED_SUBRESOURCE pdata;
	Direct3D::pContext->Map(pConstantBuffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &pdata);	// GPU����̃f�[�^�A�N�Z�X���~�߂�
	memcpy_s(pdata.pData, pdata.RowPitch, (void*)(&cb), sizeof(cb));	// �f�[�^��l�𑗂�
	Direct3D::pContext->Unmap(pConstantBuffer_, 0);	//�ĊJ
}

void FBX::SetBufferToPipeline()
{
	//���_�o�b�t�@
	UINT stride = sizeof(VERTEX);
	UINT offset = 0;
	Direct3D::pContext->IASetVertexBuffers(0, 1, &pVertexBuffer_, &stride, &offset);

	// �C���f�b�N�X�o�b�t�@�[���Z�b�g
	stride = sizeof(int);
	offset = 0;
	Direct3D::pContext->IASetIndexBuffer(pIndexBuffer_, DXGI_FORMAT_R32_UINT, 0);

	//�R���X�^���g�o�b�t�@
	Direct3D::pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer_);	//���_�V�F�[�_�[�p	
	//Direct3D::pContext->PSSetConstantBuffers(0, 1, &pConstantBuffer_);	//�s�N�Z���V�F�[�_�[�p
}

void FBX::InitMaterial(fbxsdk::FbxNode* pNode)
{
	pMaterialList_ = std::vector<MATERIAL>(materialCount_);
	for (int i = 0; i < materialCount_; i++) {
		//i�Ԗڂ̃}�e���A�������擾
		FbxSurfaceMaterial* pMaterial = pNode->GetMaterial(i);

		//�e�N�X�`�����
		FbxProperty  lProperty = pMaterial->FindProperty(FbxSurfaceMaterial::sDiffuse);

		//�e�N�X�`���̐���
		int fileTextureCount = lProperty.GetSrcObjectCount<FbxFileTexture>();

		//�e�N�X�`������
		if (fileTextureCount>0)
		{
			FbxFileTexture* textureInfo = lProperty.GetSrcObject<FbxFileTexture>(0);
			const char* textureFilePath = textureInfo->GetRelativeFileName();
			
		}

		//�e�N�X�`������
		else
		{

		}
	}
}

void FBX::Draw(Transform& transform)
{
	Direct3D::SetShader(SHADER_3D);
	//�g�����X�t�H�[�����v�Z
	transform.Calculation();
	PassDataToCB(transform);

	SetBufferToPipeline();
	//�`��
	Direct3D::pContext->DrawIndexed(indexNum_, 0, 0);
}

void FBX::Release()
{
	SAFE_RELEASE(pConstantBuffer_);
	SAFE_RELEASE(pIndexBuffer_);
	SAFE_RELEASE(pVertexBuffer_);
}
