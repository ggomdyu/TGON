#include "stdafx.h"
#include "Direct3D9.h"

CDirect3D9::CDirect3D9( ) :
m_pd3d9( Direct3DCreate9( D3D_SDK_VERSION ) ),
m_vEye( 0.0f, 3.0f, -5.0f ),
m_vLookAt( 0.0f, 0.0f, 0.0f ),
m_vUp( 0.0f, 1.0f, 0.0f )
{
	if ( !m_pd3d9 )
	{
		msg::out << "Failed to call IDirect3D9::CreateDevice function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
	}
}

CDirect3D9::~CDirect3D9( )
{

}

bool CDirect3D9::Initialize( HWND hWnd )
{
	RECT rt;
	GetClientRect( hWnd, &rt );
	//GetWindowRect( hWnd, &rt );

	if ( ( m_pd3d9 = Direct3DCreate9( D3D_SDK_VERSION ) ) == nullptr )
	{
		msg::out << "Failed to call IDirect3D9::CreateDevice function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
	}

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory( &d3dpp, sizeof( d3dpp ) );

	d3dpp.BackBufferWidth = rt.right - rt.left;
	d3dpp.BackBufferHeight = rt.bottom - rt.top;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	d3dpp.MultiSampleQuality = 0;
	/*d3dpp.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
	d3dpp.MultiSampleQuality = D3DMULTISAMPLE_2_SAMPLES;*/

	if ( FAILED( m_pd3d9->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_pd3dDevice9 ) ) )
	{
		msg::out << "Failed to call IDirect3D9::CreateDevice function.\n\n" << __FILE__ << " (" << __LINE__ << ")" << msg::warn;
		abort( );
	}

	m_pd3dDevice9->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	m_pd3dDevice9->SetRenderState( D3DRS_LIGHTING, FALSE );
	m_pd3dDevice9->SetRenderState( D3DRS_ZENABLE, TRUE );

	return true;
}

void CDirect3D9::BeginDraw( )
{
	m_pd3dDevice9->Clear( 0, NULL, D3DCLEAR_TARGET, 0x000000, 1.0f, 0 );

	if ( SUCCEEDED( m_pd3dDevice9->BeginScene( ) ) )
	{
		SetMatrices( );
	}
}

void CDirect3D9::EndDraw( )
{
	m_pd3dDevice9->EndScene( );
	m_pd3dDevice9->Present( NULL, NULL, NULL, NULL );
}

D3DXMATRIXA16*	CDirect3D9::SetView( D3DXVECTOR3* pvEye, D3DXVECTOR3* pvLookat, D3DXVECTOR3* pvUp )
{
	m_vEye = *pvEye;
	m_vLookAt = *pvLookat;
	m_vUp = *pvUp;
	D3DXVec3Normalize( &m_vView, &( m_vLookAt - m_vEye ) );
	//D3DXVec3Cross( &m_vCross, &m_vUp, &m_vView );

	D3DXMatrixLookAtLH( &matView, &m_vEye, &m_vLookAt, &m_vUp );

	return &matView;
}

D3DXMATRIXA16* CDirect3D9::MoveLocalX( float dist )
{
	D3DXVECTOR3 vNewEye = m_vEye;
	D3DXVECTOR3 vNewDst = m_vLookAt;

	D3DXVECTOR3 vMove;
	D3DXVec3Normalize( &vMove, &m_vView );
	vMove *= dist;
	vNewEye += vMove;
	vNewDst += vMove;

	return SetView( &vNewEye, &vNewDst, &m_vUp );
}

void CDirect3D9::SetMatrices( )
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixTranslation( &matWorld, 0.0f, 0.0f, 0.0f );
	m_pd3dDevice9->SetTransform( D3DTS_WORLD, &matWorld );

	static float x, y;
	if ( GetAsyncKeyState( VK_LEFT ) & 0x8000 )
		MoveLocalX( -0.1f );
	if ( GetAsyncKeyState( VK_RIGHT ) & 0x8000 )
		MoveLocalX( 0.1f );
	if ( GetAsyncKeyState( VK_DOWN ) & 0x8000 )
		y -= 0.1f;
	if ( GetAsyncKeyState( VK_UP ) & 0x8000 )
		y += 0.1f;

	D3DXMatrixLookAtLH( &matView, &m_vEye, &m_vLookAt, &m_vUp );
	m_pd3dDevice9->SetTransform( D3DTS_VIEW, &matView );


	/*	D3DXMatrixPerspectiveFovLH receive the follow arguments; FOV, Aspect ratio, Near/Far clipping plane
		FOV : https://namu.wiki/w/FOV
		Aspect ratio ¡æ http://www.slingmedia.co.kr/object/KB-005350.html */
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );
	//D3DXMatrixOrthoLH(&matProj, 1280, 720, 1.0f, 100.0f );
	m_pd3dDevice9->SetTransform( D3DTS_PROJECTION, &matProj );
}