#include "ToolManager.h"


CToolManager::CToolManager( void )
{
	m_pLoadMgr = nullptr;
}


CToolManager::~CToolManager( void )
{

}

HRESULT CToolManager::TOOLINIT( HWND hWnd, bool isWindow )
{
	if ( FAILED( Direct3D( )->Initialize( hWnd, isWindow ) ) )
	{
		return E_FAIL;
	}

	m_pLoadMgr = new CLoadManager( );
	//m_pLoadMgr->SetUpVertexData( );

	return S_OK;
}

void CToolManager::TOOLUNINIT( )
{
	m_pLoadMgr->Release( );

	Direct3D( )->Release( );
	Direct3D( )->DestroyInstance( );

	//this->DestroyInstance( );
}

void CToolManager::Update( )
{

}

void CToolManager::InputUpdate( )
{

}

void CToolManager::Render( )
{
	Direct3D( )->Render( );
}
