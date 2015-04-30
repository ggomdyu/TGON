#include "LoadManager.h"


CLoadManager::CLoadManager( void )
{
	m_pFBXLoader = new CFBXLoader( );
}


CLoadManager::~CLoadManager( void )
{

}

HRESULT CLoadManager::LoadModel( LPSTR FilePath, LPSTR FileFormat )
{
	if ( FileFormat == "FBX" )
	{
		if ( m_pFBXLoader == nullptr )
		{
			m_pFBXLoader = new CFBXLoader( );
		}

		if ( FAILED( m_pFBXLoader->LoadFBX( FilePath ) ) )
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

void CLoadManager::SetUpVertexData( )
{
	for ( int i = 0; i < m_pFBXLoader->GetNodesCount( ); i++ )
	{
		CUSTOMVERTEX* pVertices = new CUSTOMVERTEX;

		/*pVertices->m_fX = static_cast< float >( m_pFBXLoader->GetNode( i ).m_POSITIONS[ i ].mData[ 0 ] );
		pVertices->m_fY = static_cast< float >( m_pFBXLoader->GetNode( i ).m_POSITIONS[ i ].mData[ 1 ] );
		pVertices->m_fZ = static_cast< float >( m_pFBXLoader->GetNode( i ).m_POSITIONS[ i ].mData[ 2 ] );*/

		pVertices->m_fX = static_cast< float >( m_pFBXLoader->GetNode( i ).m_NORMALS[ i ].mData[ 0 ] );
		pVertices->m_fY = static_cast< float >( m_pFBXLoader->GetNode( i ).m_NORMALS[ i ].mData[ 0 ] );
		pVertices->m_fZ = static_cast< float >( m_pFBXLoader->GetNode( i ).m_NORMALS[ i ].mData[ 0 ] );

		pVertices->m_fRHW = 1.0f;
		pVertices->m_dwColor = 0xffff0000;

		Direct3D( )->GetVertexVector( )->push_back( pVertices );
	}
}

void CLoadManager::Release( )
{
	if ( m_pFBXLoader != nullptr )
	{
		m_pFBXLoader->Release( );
		delete m_pFBXLoader;
		m_pFBXLoader = nullptr;
	}
}
