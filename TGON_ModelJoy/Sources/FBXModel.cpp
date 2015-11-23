#include "stdafx.h"
#include "FBXModel.h"

#include "Direct3D9.h"
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
	D3DXMATRIXA16 matLocal;
	D3DXMatrixScaling(&matLocal, 0.005f, 0.006f, 0.005f);
	CDirect3D9::get()->GetD3DDevice()->SetTransform( D3DTS_WORLD, &matLocal);

	CDirect3D9::get( )->GetD3DDevice( )->SetStreamSource( 0, m_pVB, 0, sizeof( ModelVertex ));
	CDirect3D9::get( )->GetD3DDevice( )->SetFVF( D3DFVF_CUSTOMVERTEX );
	CDirect3D9::get( )->GetD3DDevice( )->DrawPrimitive( D3DPT_TRIANGLELIST, 0, m_pFbxMesh->GetPolygonCount( ));
}

void CFBXModel::LoadMesh( const char* const szFilePath )
{
	FBX::LoadAttributes( szFilePath, m_pFbxScene, m_pFbxMesh );

	m_vertices.reserve( m_pFbxMesh->GetPolygonCount( )*3 );

	const unsigned int uPolyCount = m_pFbxMesh->GetPolygonCount( );
	unsigned int uVertexCount = 0;
	unsigned int uVertexIndex = 0;

	for ( unsigned int i =0; i < uPolyCount; ++i )
	{
		// Get number of vertices in current poly
		uVertexCount = m_pFbxMesh->GetPolygonSize( i );
		assert( uVertexCount == 3 );

		for ( unsigned int j =0; j <uVertexCount; ++j )
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
				ModelVertex {
					static_cast<float>( fbxVertex[0] ),
					static_cast<float>( fbxVertex[1] ),
					static_cast<float>( fbxVertex[2] ),
					D3DCOLOR_ARGB( 255, 0, 0, 255 )
				}
			);
		}
	}	

	SetUpVertices( );
}

void CFBXModel::SetUpVertices( )
{
	if ( FAILED( CDirect3D9::get( )->GetD3DDevice( )->CreateVertexBuffer( m_pFbxMesh->GetPolygonCount( )*3*sizeof( ModelVertex ),
			0, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &m_pVB, nullptr )))
	{
		msg::out << "Failed to call IDirect3D9Device::CreateVertexBuffer function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
		return;
	}

	ModelVertex* pVertices( nullptr );
	if ( FAILED( m_pVB->Lock( 0, m_pFbxMesh->GetPolygonCount( ), ( void** )&pVertices, 0 )))
	{
		msg::out << "Failed to call IDirect3DVertexBuffer9::Lock function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
		return;
	}

	memcpy( pVertices, &m_vertices[0], m_vertices.size( )*sizeof( ModelVertex ));
	m_pVB->Unlock( );
}