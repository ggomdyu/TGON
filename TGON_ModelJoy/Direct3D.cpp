#include "Direct3D.h"


CDirect3D::CDirect3D( )
{
	m_pD3D9 = nullptr;
	m_pD3DDevice9 = nullptr;
	m_pVB = nullptr;
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

	m_pD3DDevice9->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	/*m_pD3DDevice9->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, TRUE );
	m_pD3DDevice9->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE );*/
	m_pD3DDevice9->SetRenderState( D3DRS_ZENABLE, TRUE );

	return S_OK;
}

HRESULT CDirect3D::InitializeVB( )
{

	if ( FAILED( m_pD3DDevice9->CreateVertexBuffer( m_Vertexs.size( ) * sizeof( CUSTOMVERTEX ), 0, D3DFVF_CUSTOMVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL ) ) )
	{
		return E_FAIL;
	}

	CUSTOMVERTEX* pVertices;

	if ( FAILED( m_pVB->Lock( 0, 0, ( void** )&pVertices, 0 ) ) )
	{
		return E_FAIL;
	}

	for ( int i = 0; i < m_Vertexs.size( ); i++ )
	{
		pVertices[ i ].m_fX = m_Vertexs[ i ]->m_fX;
		pVertices[ i ].m_fY = m_Vertexs[ i ]->m_fY;
		pVertices[ i ].m_fZ = m_Vertexs[ i ]->m_fZ;

		pVertices[ i ].m_fRHW = m_Vertexs[ i ]->m_fRHW;
		pVertices[ i ].m_dwColor = m_Vertexs[ i ]->m_dwColor;
	}

	m_pVB->Unlock( );

	return S_OK;
}

void CDirect3D::SetMatrices( )
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity( &matWorld );

	m_pD3DDevice9->SetTransform( D3DTS_WORLD, &matWorld );

	D3DXVECTOR3 vEyePt( 0.0f, 0.3f, -5.0f );
	D3DXVECTOR3 vLookatPos( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec( 0.0f, 0.0f, 0.0f );
	D3DXMATRIXA16 matView;

	D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPos, &vUpVec );
	m_pD3DDevice9->SetTransform( D3DTS_VIEW, &matView );

	D3DXMATRIXA16 matProj;

	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
	m_pD3DDevice9->SetTransform( D3DTS_PROJECTION, &matProj );

}

void CDirect3D::Release( )
{
	std::vector<CUSTOMVERTEX*>::iterator iter;

	for ( iter = m_Vertexs.begin( ); iter != m_Vertexs.end( ); iter++ )
	{
		delete ( *iter );
		*iter = nullptr;
	}

	if ( m_pVB != nullptr )
	{
		m_pVB->Release( );
		m_pVB = nullptr;
	}

	if ( m_pD3DDevice9 != nullptr )
	{
		m_pD3DDevice9->Release( );
		m_pD3DDevice9 = nullptr;
	}

	if ( m_pD3D9 != nullptr )
	{
		m_pD3D9->Release( );
		m_pD3D9 = nullptr;
	}
}

void CDirect3D::Render( )
{
	m_pD3DDevice9->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0F, 0 );

	if ( SUCCEEDED( m_pD3DDevice9->BeginScene( ) ) )
	{
		SetMatrices( );

		m_pD3DDevice9->SetStreamSource( 0, m_pVB, 0, sizeof( CUSTOMVERTEX ) );
		m_pD3DDevice9->SetFVF( D3DFVF_CUSTOMVERTEX );
		m_pD3DDevice9->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, static_cast< int >( m_Vertexs.size( ) ) );
		//m_pD3DDevice9->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );

		m_pD3DDevice9->EndScene( );
	}
	m_pD3DDevice9->Present( NULL, NULL, NULL, NULL );
}
