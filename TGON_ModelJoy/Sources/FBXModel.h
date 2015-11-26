/*
* 작성자 : 김태우
* 작성일 : 2015-04-25
* 최종 수정 : 차준호
* 최종 수정일 : 2015-11-12
*/
#pragma once
#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <fbxsdk.h>
	#include <vector>
	#include <atlbase.h>
#endif

#include "ModelBase.h"

class CFBXModel : public IModelBase
{
private:
	struct ModelVertex
	{
		float x, y, z;
		DWORD dwColor;
	};

public:
	CFBXModel( _In_ const char* const szFilePath = nullptr );
	~CFBXModel( );

	virtual void Render( ) override;

public:
	virtual void LoadMesh( _In_ const char* const szFilePath ) override;
	virtual void LoadAnim( ) override; // 임시 FBX는 FBX Scene을 사용하지만 다른 모델들은 모르니 일단 보류

private:
	void SetUpVertices( );

public:
	FbxScene* m_pFbxScene;
	FbxMesh* m_pFbxMesh;

	CComPtr<IDirect3DVertexBuffer9> m_pVB;
	std::vector<ModelVertex> m_vertices;

	D3DXMATRIX m_matLocal;
};

