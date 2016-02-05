#include "stdafx.h"
#include "FbxModel.h"

#include <Console\tgConsole.h>

FbxModel::FbxModel( const char* fbxPath )
{
	FbxImporter* pFbxImporter = FbxImporter::Create( tgon::fbx::
													GetFbxManager( ).get( ), "" );

	bool isFailed = pFbxImporter->Initialize( fbxPath, -1, tgon::fbx::
							  GetFbxManager( )->GetIOSettings( ));
	tgon::tgConsole::WriteLine( (unsigned int)tgon::fbx::GetFbxManager( )->GetIOSettings( ) );

	if ( isFailed )
	{
		tgon::tgConsole::WriteLine( L"Failed to invoke FbxImporter::Initialize." );
	}


	m_pFbxScene = FbxScene::Create( tgon::fbx::GetFbxManager( ).get( ), "tempScene" );

	pFbxImporter->Import( m_pFbxScene );

	//StoreModelInformation( m_pFbxScene );

	pFbxImporter->Destroy( );
}


FbxModel::~FbxModel( )
{
}

void FbxModel::Render( )
{
	D3DXMATRIXA16 matLocal;
	D3DXMatrixScaling( &matLocal, 0.005f, 0.006f, 0.005f );
	Direct3D9::GetInstance( )->GetD3dDevice( )->SetTransform( D3DTS_WORLD, &matLocal );

	Direct3D9::GetInstance( )->GetD3dDevice( )->SetStreamSource( 0, m_pVB, 0, sizeof( ModelVertex ));
	Direct3D9::GetInstance( )->GetD3dDevice( )->SetFVF( FVF::ModelVertex_FVF );
	Direct3D9::GetInstance( )->GetD3dDevice( )->DrawPrimitive( D3DPT_TRIANGLELIST, 0, m_pFbxMesh->GetPolygonCount( ) );
}

void FbxModel::DrawRecursive( FbxNode* pNode, FbxAMatrix& pParentGlobalPosition )
{
	FbxAMatrix matGlobalPosition = pNode->EvaluateGlobalTransform( 0 );

	// Find out what type of node this is
	FbxNodeAttribute* pNodeAttribute = pNode->GetNodeAttribute( );

	if ( pNodeAttribute )
	{
		switch ( pNodeAttribute->GetAttributeType( ))
		{
		case FbxNodeAttribute::eMesh:
			{
				FbxAMatrix matGeometryOffset = GetGeometricOffset( pNode );
				FbxAMatrix matGlobalOffsetPosition = matGlobalPosition * matGeometryOffset;

				DrawMesh( pNode, matGlobalOffsetPosition );
			}
			break;
		}
	}

	const int childCount = pNode->GetChildCount( );
	
	for ( int i = 0; i < childCount; ++i )
	{
		DrawRecursive( pNode->GetChild( i ), matGlobalPosition );
	}
}

const FbxAMatrix FbxModel::GetGeometricOffset( FbxNode* pNode )
{
	const FbxVector4 matTrans = pNode->GetGeometricTranslation( FbxNode::eSourcePivot );
	const FbxVector4 matRot = pNode->GetGeometricRotation( FbxNode::eSourcePivot );
	const FbxVector4 matScale = pNode->GetGeometricScaling( FbxNode::eSourcePivot );

	return FbxAMatrix( matTrans, matRot, matScale );
}

void FbxModel::StoreModelInformation( FbxScene * pNode )
{
	//RecurseModelData( pNode->GetRootNode( ));
}

void FbxModel::DrawMesh( FbxNode* pNode, FbxAMatrix& pParentGlobalPosition )
{
	FbxMesh* pFbxMesh = pNode->GetMesh( );
	const int vertexCount = pFbxMesh->GetControlPointsCount( );

	if ( vertexCount == 0 )
		return;

	// Get the Vertex array. This could be fetched from the node itselt or better from a cache
	FbxVector4* pVertexArray = nullptr;
	pVertexArray = new FbxVector4[vertexCount];

	const int polygonCount = pFbxMesh->GetPolygonCount( );
	for ( int i = 0; i < polygonCount; ++i )
	{

	}

	delete[] pVertexArray;
}


void FbxModel::SetUpVertices( )
{
	if ( FAILED( Direct3D9::GetInstance( )->GetD3dDevice( )->CreateVertexBuffer( m_pFbxMesh->GetPolygonCount( ) * 3 * sizeof( ModelVertex ),
		0, FVF::ModelVertex_FVF, D3DPOOL_MANAGED, &m_pVB, nullptr ) ) )
	{
		msg::out << "Failed to call IDirect3D9Device::CreateVertexBuffer function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
		return;
	}

	ModelVertex* pVertices( nullptr );
	if ( FAILED( m_pVB->Lock( 0, m_pFbxMesh->GetPolygonCount( ), ( void** )&pVertices, 0 ) ) )
	{
		msg::out << "Failed to call IDirect3DVertexBuffer9::Lock function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
		return;
	}

	memcpy( pVertices, &m_vertices[ 0 ], m_vertices.size( )*sizeof( ModelVertex ) );
	m_pVB->Unlock( );
}


/*
void CFBXModel::LoadMesh( const char* const szFilePath )
{
	FBX::LoadAttributes( szFilePath, m_pFbxScene, m_pFbxMesh );

	m_vertices.reserve( m_pFbxMesh->GetPolygonCount( ) * 3 );

	const unsigned int uPolyCount = m_pFbxMesh->GetPolygonCount( );
	unsigned int uVertexCount = 0;
	unsigned int uVertexIndex = 0;

	for ( unsigned int i = 0; i < uPolyCount; ++i )
	{
		// Get number of vertices in current poly
		uVertexCount = m_pFbxMesh->GetPolygonSize( i );
		assert( uVertexCount == 3 );

		for ( unsigned int j = 0; j < uVertexCount; ++j )
		{
			// Get corresponding vertex index for this poly-vertex
			uVertexIndex = m_pFbxMesh->GetPolygonVertex( i, j );
			assert( uVertexIndex != -1 && "Index is out of range" );

			// Get vertex position
			FbxVector4 fbxVertex = m_pFbxMesh->GetControlPointAt( uVertexIndex );

			// Get vertex normal
			/*FbxVector4 fbxNormal;
			bool bResult = pMesh->GetPolygonVertexNormal(uPoly, uVertex, fbxNormal);*/

			m_vertices.emplace_back(
				ModelVertex{
				static_cast< float >( fbxVertex[ 0 ] ),
				static_cast< float >( fbxVertex[ 1 ] ),
				static_cast< float >( fbxVertex[ 2 ] ),
				D3DCOLOR_ARGB( 255, 0, 0, 255 )
			}
			);
		}
	}

	SetUpVertices( );
}

*/