#include "Direct3D.h"


CDirect3D::CDirect3D( )
{
	m_pD3D9 = nullptr;
	m_pD3DDevice9 = nullptr;
}


CDirect3D::~CDirect3D( )
{

}

HRESULT CDirect3D::Initialize( HWND hWnd, bool isWindow )
{
	if ( ( m_pD3D9 = Direct3DCreate9( D3D_SDK_VERSION ) ) == NULL )
	{
		MessageBox( hWnd, L"Direct3DCreate9 Error....!!!!", L"ERROR!!!", MB_OK );
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );

	RECT rt;
	GetClientRect( hWnd, &rt );

	d3dpp.BackBufferWidth = rt.right;
	d3dpp.BackBufferHeight = rt.bottom;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = isWindow;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	HRESULT hr;
	if ( FAILED( hr = m_pD3D9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pD3DDevice9 ) ) )
	{
		MessageBox( hWnd, L"CreateDevice Error!", L"ERROR!!!", MB_OK );
		return hr;
	}

	m_pD3DDevice9->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, TRUE );
	m_pD3DDevice9->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE );
}

void CDirect3D::Release( )
{
	if ( m_pD3DDevice9 != NULL )
	{
		m_pD3DDevice9->Release( );
		m_pD3DDevice9 = nullptr;
	}

	if ( m_pD3D9 != NULL )
	{
		m_pD3D9->Release( );
		m_pD3D9 = nullptr;
	}
}

void CDirect3D::Render( )
{
	m_pD3DDevice9->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 255, 0, 0, 255 ), 1000.0F, 0 );

	if ( SUCCEEDED( m_pD3DDevice9->BeginScene( ) ) )
	{
		m_pD3DDevice9->EndScene( );
	}
	m_pD3DDevice9->Present( NULL, NULL, NULL, NULL );
}
