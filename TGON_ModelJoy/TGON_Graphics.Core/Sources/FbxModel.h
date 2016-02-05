#pragma once
#include <tgFbx.h>
#include <Windows.h>
#include <atlbase.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>


class FbxModel
{
	struct ModelVertex
	{
		float x, y, z;
		DWORD dwColor;
	};


public:
	FbxModel( const char* fbxPath );
	~FbxModel( );

	void Render( );
	void SetUpVertices( );


	void DrawRecursive( FbxNode* pNode, FbxAMatrix& pParentGlobalPosition );

private:
	const FbxAMatrix GetGeometricOffset( FbxNode* pNode );
	void StoreModelInformation( FbxScene* pNode );

	void DrawMesh( FbxNode* pNode, FbxAMatrix& pParentGlobalPosition );

private:
	FbxScene* m_pFbxScene;

	CComPtr<IDirect3DVertexBuffer9> m_pVB;
	std::vector<ModelVertex> m_vertices;
};

