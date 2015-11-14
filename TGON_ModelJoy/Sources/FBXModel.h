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

#include "BaseModel.h"
#include "Singleton.h"

class CFBXModel : public BaseModel
{
public:
	CFBXModel( _In_ const char* const szFilePath = nullptr );
	~CFBXModel( );

	virtual void Render( ) override;

public:
	virtual bool LoadMesh( _In_ const char* const szFilePath ) override;

private:
	void ImportFBX( _In_ const char* const szFilePath );

private:
	FbxScene* m_pFbxScene;
	FbxMesh* m_pFbxMesh;

	D3DXMATRIX m_matLocal;
	CComPtr<IDirect3DVertexBuffer9> m_pVB;
	std::vector<CUSTOMVERTEX> m_vertices;
};

