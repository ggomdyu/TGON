#include "stdafx.h"
#include "Direct3D9Device.h"

#include <cassert>
#include <DxErr.h>


#pragma comment( lib, "DxErr.lib" )


tgon::Direct3D9Device::Direct3D9Device( )
	/*m_eye( 0.0f, 3.0f, -5.0f ),
	m_lookAt( 0.0f, 0.0f, 0.0f ), d3d 카메라에 넣기
	m_up( 0.0f, 1.0f, 0.0f )*/
{
	
	Direct3DCreate9Ex( D3D_SDK_VERSION, &m_d3d );


	if ( !m_d3d )
	{
		MessageBox( GetFocus(), L"Failed to call Direct3DCreate9.", L"WARNING!",
					MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}
}


tgon::Direct3D9Device::~Direct3D9Device( )
{

}


bool tgon::Direct3D9Device::Setup( const GraphicsDeviceCreateParam& gdcp )
{
	m_presentWnd = gdcp.presentWnd;

	const D3DDEVTYPE d3dDeviceType = ( gdcp.gdpt == GraphicsDeviceProcessType::kHardware ) ?
		D3DDEVTYPE_HAL : D3DDEVTYPE_REF;

	const DWORD d3dBehaviorFlag = ( gdcp.gdpt == GraphicsDeviceProcessType::kHardware ) ?
		D3DCREATE_HARDWARE_VERTEXPROCESSING :
			D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	const D3DFORMAT surfaceFormat = D3DFORMAT::D3DFMT_A8R8G8B8;

	const bool isWindowed = true;

//	m_d3d->CheckDeviceMultiSampleType( NULL, d3dDeviceType, surfaceFormat, );

	RECT rt;
	GetClientRect( gdcp.presentWnd, &rt );

	D3DPRESENT_PARAMETERS pp = { 0 };
	pp.hDeviceWindow = gdcp.presentWnd;
	pp.BackBufferWidth = rt.right;
	pp.BackBufferHeight = rt.bottom;
	pp.BackBufferFormat = D3DFMT_UNKNOWN;// D3DFORMAT::D3DFMT_A8R8G8B8;
	pp.BackBufferCount = 1;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.Windowed = isWindowed;
	// TW Labtop Set
	pp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	pp.MultiSampleQuality = 0;
	//
	/*d3dpp.MultiSampleType = D3DMULTISAMPLE_NONMASKABLE;
	d3dpp.MultiSampleQuality = D3DMULTISAMPLE_2_SAMPLES;*/


	HRESULT hr;
	hr = this->CreateDevice( d3dDeviceType, d3dBehaviorFlag, pp );

	if ( FAILED( hr ))
	{
		// TODO : Make messagebox function seems like printf, and use it with under string variable
		LPCTSTR errString = DXGetErrorDescription( hr );
		MessageBox( GetFocus( ), L"Failed to call IDirect3D9Device::CreateDevice.", L"WARNING!",
					MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}
	

	GetD3dDevice( )->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	GetD3dDevice( )->SetRenderState( D3DRS_LIGHTING, FALSE );
	GetD3dDevice( )->SetRenderState( D3DRS_ZENABLE, TRUE );

	return true;
}


HRESULT tgon::Direct3D9Device::CreateDevice( D3DDEVTYPE d3dDeviceType, DWORD d3dBehaviorFlag,
												D3DPRESENT_PARAMETERS& pp )
{
	/*D3DDISPLAYMODEEX displayModeEx;
	displayModeEx.RefreshRate = 60;*/ // I think it will be good If using XML
	
	HRESULT hr;
	hr = m_d3d->CreateDeviceEx( D3DADAPTER_DEFAULT, d3dDeviceType, pp.hDeviceWindow,
							  d3dBehaviorFlag, &pp, NULL, &m_d3dDevice );
	
	return hr;
}


void tgon::Direct3D9Device::Display( )
{
	assert( m_d3dDevice.p );

	GetD3dDevice( )->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB( 255, 0, 0, 255 ), 1.0f, 0 );


	if ( SUCCEEDED( GetD3dDevice( )->BeginScene( )))
	{



		GetD3dDevice( )->EndScene( );
	}


	GetD3dDevice( )->Present( NULL, NULL, NULL, NULL );


	/*assert( m_d3dDevice.p );

	HRESULT hr;


	if ( FAILED( hr = m_d3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
						D3DCOLOR_ARGB( 255, 0, 0, 255 ), 1.0f, 0 )))
	{
		LPCTSTR errString = DXGetErrorString( hr );
		MessageBox( GetFocus( ), errString, L"WARNING!",
					MB_OK | MB_ICONEXCLAMATION );
		return;
	}

	if ( FAILED( hr = m_d3dDevice->BeginScene( )))
	{
		LPCTSTR errString = DXGetErrorDescription( hr );
		MessageBox( GetFocus( ), errString, L"WARNING!",
					MB_OK | MB_ICONEXCLAMATION );
		return;
	}*/

	//SetMatrices( );
	//if ( FAILED( hr = GetD3dDevice( )->Present( nullptr, nullptr, NULL, nullptr )))
	//{
	//	LPCTSTR errString = DXGetErrorDescription( hr );
	//	MessageBox( GetFocus( ), errString, L"WARNING!",
	//				MB_OK | MB_ICONEXCLAMATION );
	//	return;
	//}
}

//void tgon::Direct3D9Device::EndDraw( )
//{
	/*GetD3dDevice( )->EndScene( );
	GetD3dDevice( )->Present( NULL, NULL, NULL, NULL );*/
//}
//
//void tgon::Direct3D9Device::MakeView( D3DXVECTOR3& eye, D3DXVECTOR3& lookAt, D3DXVECTOR3& up )
//{
//	m_eye = eye;
//	m_lookAt = lookAt;
//	m_up = up;
//
//	D3DXVec3Normalize( &m_vView, &( m_lookAt-m_eye ));
//	//D3DXVec3Cross( &m_vCross, &m_vUp, &m_vView );
//
//	D3DXMatrixLookAtLH( &m_matView, &m_eye, &m_lookAt, &m_up );
//}
//
//void tgon::Direct3D9Device::DrawLine( const D3DXVECTOR3& p1, const D3DXVECTOR3& p2, DWORD color )
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
//
//void tgon::Direct3D9Device::MoveLocalX( float dist )
//{
//	D3DXVECTOR3 vNewEye = m_eye;
//	D3DXVECTOR3 vNewDst = m_lookAt;
//
//	D3DXVECTOR3 vMove( 0.0f, 1.0f, 1.0f );
//	//D3DXVec3Normalize( &vMove, &m_vView );
//	//msg::out << vMove.x << " / " << vMove.y << " / " << vMove.z << msg::warn;
//	
//	vMove *= dist;
//	vNewEye += vMove;
//	vNewDst += vMove;
//
//	MakeView( vNewEye, vNewDst, m_up );
//}
//
//void tgon::Direct3D9Device::SetMatrices( )
//{
//	D3DXMATRIXA16 matWorld;
//	D3DXMatrixTranslation( &matWorld, 0.0f, 0.0f, 0.0f );
//	m_d3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
//
//	static float x, y;
//	if ( GetAsyncKeyState( VK_LEFT ) & 0x8000 )
//		MoveLocalX( -0.1f );
//	if ( GetAsyncKeyState( VK_RIGHT ) & 0x8000 )
//		MoveLocalX( 0.1f );
//	if ( GetAsyncKeyState( VK_DOWN ) & 0x8000 )
//		y -= 0.1f;
//	if ( GetAsyncKeyState( VK_UP ) & 0x8000 )
//		y += 0.1f;
//
//	D3DXMatrixLookAtLH( &m_matView, &m_eye, &m_lookAt, &m_up );
//	m_d3dDevice->SetTransform( D3DTS_VIEW, &m_matView );
//
//
//	/*	D3DXMatrixPerspectiveFovLH receive the arguments: FOV, Aspect ratio, Near/Far clipping plane
//		FOV : https://namu.wiki/w/FOV
//		Aspect ratio → http://www.slingmedia.co.kr/object/KB-005350.html */
//	D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI/4, 1.0f, 1.0f, 1000.0f );
//	//D3DXMatrixOrthoLH(&matProj, 1280, 720, 1.0f, 100.0f );
//	m_d3dDevice->SetTransform( D3DTS_PROJECTION, &m_matProj );
//}
//

//bool tgon::GraphicsDevice::IsAble( )
//{
//	return false;
//}
