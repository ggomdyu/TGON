#include "stdafx.h"
#include "FBXModel.h"

#include "Direct3D.h"
#include "FBX.h"

CFBXModel::CFBXModel( const char* const szFilePath ) :
	m_pFbxScene( FbxScene::Create( FBX::GetManager( ), "" )),
	m_pFbxMesh( nullptr )
{
	D3DXMatrixIdentity( &m_matLocal );

	if ( szFilePath ) {
		LoadMesh( szFilePath );
	}
}

CFBXModel::~CFBXModel( )
{
}

void CFBXModel::Render( )
{
	CDirect3D::get( )->GetD3DDevice( )->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ));
	CDirect3D::get( )->GetD3DDevice( )->SetFVF( D3DFVF_CUSTOMVERTEX );
	CDirect3D::get( )->GetD3DDevice( )->DrawPrimitive( D3DPT_TRIANGLELIST, 0, m_pFbxMesh->GetPolygonCount( ));
}

bool CFBXModel::LoadMesh( const char* const szFilePath )
{
	this->ImportFBX( szFilePath );
	FBX::LoadAttributes( szFilePath, m_pFbxScene, m_pFbxMesh );

	const unsigned int uPolyCount = m_pFbxMesh->GetPolygonCount( );
	unsigned int uVertexCount = 0;

	for ( unsigned int i =0; i < uPolyCount; ++i )
	{
		// Get number of vertices in current poly - is your mesh triangulated?
		uVertexCount = m_pFbxMesh->GetPolygonSize( i );

		for ( unsigned int j =0; j <uVertexCount; ++j )
		{
			// Get corresponding vertex index for this poly-vertex
			unsigned int uVertexIndex = m_pFbxMesh->GetPolygonVertex( i, j );
			assert( uVertexIndex != -1 && "Index is out of range" );

			// Get vertex position
			FbxVector4 fbxVertex = m_pFbxMesh->GetControlPointAt( uVertexIndex );

			// Get vertex normal
			/*FbxVector4 fbxNormal;
			bool bResult = pMesh->GetPolygonVertexNormal(uPoly, uVertex, fbxNormal);*/

			m_vertices.emplace_back(
				CUSTOMVERTEX {
					static_cast<float>( fbxVertex[0] ),
					static_cast<float>( fbxVertex[1] ),
					static_cast<float>( fbxVertex[2] ),
				0, 0x00ff00 }
			);
		}
	}
/*
	CUSTOMVERTEX vertices[]
	{
		{ 0, 0, 0, 0, 0xff0000 },
		{ 0, 500, 0, 0, 0xff0000 },
		{ 500, 0, 0, 0, 0xff0000 },
	};
*/
	if ( FAILED( CDirect3D::get( )->GetD3DDevice( )->CreateVertexBuffer( uPolyCount*3*sizeof( CUSTOMVERTEX ),
			0, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &m_pVB, nullptr )))
	{
		msg::out << "Failed to call IDirect3D9Device::CreateVertexBuffer function." << msg::warn;
		return false;
	}

	CUSTOMVERTEX* pVertices = nullptr;
	if ( FAILED( m_pVB->Lock( 0, 0, ( void** )&pVertices, 0 )))
	{
		msg::out << "Failed to call IDirect3DVertexBuffer9::Lock function." << msg::warn;
		return false;
	}

	memcpy( pVertices, &m_vertices[0], m_vertices.size( )*sizeof(CUSTOMVERTEX) );
	m_pVB->Unlock( );

	return true;
}

void CFBXModel::ImportFBX( const char* const szFilePath )
{
	FbxImporter* const pImporter( FbxImporter::Create( FBX::GetManager( ), "" ));
	assert( pImporter != nullptr );

	if ( !pImporter->Initialize( szFilePath )) {
		msg::out << "Failed to load FBX. ( " << szFilePath << " )" << msg::warn;
		abort( );
	}

	if ( !pImporter->Import( m_pFbxScene )) {
		msg::out << "Failed to load FBX. ( " << szFilePath << " )" << msg::warn;
		abort( );
	}
}
