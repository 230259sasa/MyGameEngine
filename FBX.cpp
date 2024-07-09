#include "FBX.h"

FBX::FBX()
    :pVertexBuffer_(nullptr), pIndexBuffer_(nullptr), pConstantBuffer_(nullptr),
    vertexCount_(-1),polygonCount_(-1)
{
}

HRESULT FBX::Load(std::string fileName)
{
	//マネージャを生成
	FbxManager* pFbxManager = FbxManager::Create();

	//インポーターを生成
	FbxImporter* fbxImporter = FbxImporter::Create(pFbxManager, "imp");
	fbxImporter->Initialize(fileName.c_str(), -1, pFbxManager->GetIOSettings());

	//シーンオブジェクトにFBXファイルの情報を流し込む
	FbxScene* pFbxScene = FbxScene::Create(pFbxManager, "fbxscene");
	fbxImporter->Import(pFbxScene);
	fbxImporter->Destroy();

	//マネージャ解放
	pFbxManager->Destroy();
	return S_OK;
}

void FBX::Draw(Transform& transform)
{
}

void FBX::Release()
{
}
