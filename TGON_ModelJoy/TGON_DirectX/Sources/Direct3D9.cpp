//#include "stdafx.h"
#include "Direct3D9.h"

#include "D3dFVF.h"

Direct3D9::Direct3D9( ) :
	m_d3d( Direct3DCreate9( D3D_SDK_VERSION )),
	m_eye( 0.0f, 3.0f, -5.0f ),
	m_lookAt( 0.0f, 0.0f, 0.0f ),
	m_up( 0.0f, 1.0f, 0.0f )
{
	if ( !m_d3d )
	{
		MessageBox( GetFocus( ), L"Failed to call Direct3DCreate9.", L"WARNING!",
					MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}
}

Direct3D9::~Direct3D9( )
{

}

bool Direct3D9::Initialize( HWND hWnd )
{
	RECT rt;
	GetClientRect( hWnd, &rt );

	D3DPRESENT_PARAMETERS d3dpp = { 0 };
	d3dpp.BackBufferWidth = rt.right;
	d3dpp.BackBufferHeight = rt.bottom;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;
	// TW Labtop Set
	d3dpp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	d3dpp.MultiSampleQuality = 0;
	//
	/*d3dpp.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
	d3dpp.MultiSampleQuality = D3DMULTISAMPLE_2_SAMPLES;*/

	if ( FAILED( m_d3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &m_d3dDevice )))
	{
		MessageBox( GetFocus( ), L"Failed to call IDirect3D9::CreateDevice.", L"WARNING!",
					MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}

	m_d3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	m_d3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );
	m_d3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

	return true;
}

void Direct3D9::BeginDraw( )
{
	m_d3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, 0x000000, 1.0f, 0 );

	if ( SUCCEEDED( m_d3dDevice->BeginScene( )))
	{
		SetMatrices( );
	}
}

void Direct3D9::EndDraw( )
{
	m_d3dDevice->EndScene( );
	m_d3dDevice->Present( NULL, NULL, NULL, NULL );
}

void Direct3D9::MakeView( D3DXVECTOR3& eye, D3DXVECTOR3& lookAt, D3DXVECTOR3& up )
{
	m_eye = eye;
	m_lookAt = lookAt;
	m_up = up;

	D3DXVec3Normalize( &m_vView, &( m_lookAt-m_eye ));
	//D3DXVec3Cross( &m_vCross, &m_vUp, &m_vView );

	D3DXMatrixLookAtLH( &m_matView, &m_eye, &m_lookAt, &m_up );
}
//
//void Direct3D9::DrawLine( const D3DXVECTOR3& p1, const D3DXVECTOR3& p2, DWORD color )
//{
//	HRESULT hr;
//	m_d3dDevice->SetRenderState( D3DRS_COLORVERTEX, true );
//	m_d3dDevice->SetRenderState( D3DRS_LIGHTING, false );
//	m_d3dDevice->SetRenderState( D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1 );
//	m_d3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP, D3DTOP_SELECTARG1 );
//	m_d3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_DIFFUSE );
//	m_d3dDevice->SetTextureStageState( 1, D3DTSS_COLOROP, D3DTOP_DISABLE );
//
//	LineVertex line[2];
//	line[0].pos = p1;
//	line[0].color = color;
//	line[1].pos = p2;
//	line[1].color = color;
//
//	hr = m_d3dDevice->SetFVF( FVF::Line_FVF );
//	hr = m_d3dDevice->SetPixelShader( 0 );
//	hr = m_d3dDevice->SetVertexShader( 0 );
//
//	hr = m_d3dDevice->DrawPrimitiveUP( D3DPT_LINELIST, 1, line, sizeof( LineVertex ));
//
//	if ( FAILED( hr ))
//	{
//		//MessageBox( NULL, DXGetErrorString9(hr), "Points Error", MB_OK );
//		return;
//	}
//}

void Direct3D9::MoveLocalX( float dist )
{
	D3DXVECTOR3 vNewEye = m_eye;
	D3DXVECTOR3 vNewDst = m_lookAt;

	D3DXVECTOR3 vMove( 0.0f, 1.0f, 1.0f );
	//D3DXVec3Normalize( &vMove, &m_vView );
	//msg::out << vMove.x << " / " << vMove.y << " / " << vMove.z << msg::warn;
	
	vMove *= dist;
	vNewEye += vMove;
	vNewDst += vMove;

	MakeView( vNewEye, vNewDst, m_up );
}

void Direct3D9::SetMatrices( )
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixTranslation( &matWorld, 0.0f, 0.0f, 0.0f );
	m_d3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

	static float x, y;
	if ( GetAsyncKeyState( VK_LEFT ) & 0x8000 )
		MoveLocalX( -0.1f );
	if ( GetAsyncKeyState( VK_RIGHT ) & 0x8000 )
		MoveLocalX( 0.1f );
	if ( GetAsyncKeyState( VK_DOWN ) & 0x8000 )
		y -= 0.1f;
	if ( GetAsyncKeyState( VK_UP ) & 0x8000 )
		y += 0.1f;

	D3DXMatrixLookAtLH( &m_matView, &m_eye, &m_lookAt, &m_up );
	m_d3dDevice->SetTransform( D3DTS_VIEW, &m_matView );


	/*	D3DXMatrixPerspectiveFovLH receive the arguments: FOV, Aspect ratio, Near/Far clipping plane
		FOV : https://namu.wiki/w/FOV
		Aspect ratio ¡æ http://www.slingmedia.co.kr/object/KB-005350.html */
	D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI / 4, 1.0f, 1.0f, 1000.0f );
	//D3DXMatrixOrthoLH(&matProj, 1280, 720, 1.0f, 100.0f );
	m_d3dDevice->SetTransform( D3DTS_PROJECTION, &m_matProj );
}