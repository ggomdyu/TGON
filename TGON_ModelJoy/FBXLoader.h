#pragma once

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include "Direct3D.h"
#include <fbxsdk.h>
#include <cassert>

#pragma comment( lib, "libfbxsdk.lib" )

struct MESH_ELEMENTS
{
	unsigned int m_POSITION;
	unsigned int m_NORMAL;
};

struct FBX_MESH_NODE
{
	std::string m_MESH_NODE_NAME;
	std::string m_MESH_PARANT_NODE_NAME;

	MESH_ELEMENTS m_ELEMENTS;

	std::vector<unsigned int> m_INDEXS;
	std::vector<FbxVector4> m_POSITIONS;
	std::vector<FbxVector4> m_NORMALS;

	float MATRIX4x4[ 16 ];

	~FBX_MESH_NODE( )
	{
		Release( );
	}

	void Release( )
	{
		m_INDEXS.clear( );
		m_POSITIONS.clear( );
		m_NORMALS.clear( );
	}

};

class CFBXLoader
{
protected:
	FbxManager* m_pFBXManager;
	FbxScene* m_pFBXScene;
	FbxImporter* m_pFBXImporter;

	std::vector<FBX_MESH_NODE> m_MeshNodes;

	void InitializeFBXSDKObjects( FbxManager*& pFBXManager, FbxScene*& pFBXScene );
	void TriangulateRecursive( FbxNode* pNode );

	void SetUpNode( FbxNode* pNode, std::string parentNodeName );
	void SetUp( );

	void CopyVertexData( FbxMesh* pMesh, FBX_MESH_NODE* MeshNode );
	void ComputeNodeMatrix( FbxNode* pNode, FBX_MESH_NODE* meshNode );

	static void FBXMatrixToFloat16( FbxMatrix* pFBXMat, float dest[ 16 ] )
	{
		unsigned int nn = 0;
		for ( int i = 0; i < 4; i++ )
		{
			for ( int j = 0; j < 4; j++ )
			{
				dest[ nn ] = static_cast< float >( pFBXMat->Get( i, j ) );
				nn++;
			}
		}
	}

public:
	CFBXLoader( void );
	~CFBXLoader( void );

	HRESULT LoadFBX( LPSTR FilePath );

	FbxNode& GetRootNode( );

	inline int GetNodesCount( ) { return static_cast< int >( m_MeshNodes.size( ) ); }

	FBX_MESH_NODE&	GetNode( const unsigned int Index );

	void Release( );
};