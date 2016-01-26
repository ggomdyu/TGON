#include "stdafx.h"
#include "D3d9Device.h"

#include <cassert>
#include "D3d9Util.h"


#define _L(x)  __L(x)
#define __L(x)  L##x




tgon::D3d9Device::D3d9Device( const tgWindow& tgWnd ) :
	m_wndHandle( tgWnd.GetWindowHandle( ))
	/*m_eye( 0.0f, 3.0f, -5.0f ),
	m_lookAt( 0.0f, 0.0f, 0.0f ),
	m_up( 0.0f, 1.0f, 0.0f )*/
{
	DxErrorException( Direct3DCreate9Ex( D3D_SDK_VERSION, &m_d3d ));

	assert( tgWnd.GetWindowHandle( ));
	assert( m_d3d );
}


tgon::D3d9Device::~D3d9Device( )
{
	
}


bool tgon::D3d9Device::Setup( const GraphicsDeviceCreateParam* gdcp )
{
	assert( gdcp );

	const D3dDeviceCreateParam* d3dCreateParam = static_cast<const D3dDeviceCreateParam*>( gdcp );


	//D3DCAPS9 d3dCaps;
	//GetD3D( )->GetDeviceCaps( D3DADAPTER_DEFAULT,
	//			( d3dCreateParam->gdpt == GraphicsDeviceProcessType::kHardware ) ?
	//				D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING,
	//					  &d3dCaps );

	//int vp = 0;
	//vp = ( d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) ?
	//		D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;


//	m_d3d->CheckDeviceMultiSampleType( NULL, d3dDeviceType, surfaceFormat, );

	RECT rt;
	GetClientRect( m_wndHandle, &rt );

	D3DPRESENT_PARAMETERS pp = { 0 };
	pp.BackBufferWidth = rt.right;
	pp.BackBufferHeight = rt.bottom;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	pp.BackBufferCount = 1;
	pp.MultiSampleType = D3DMULTISAMPLE_NONE;
	pp.MultiSampleQuality = 0;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.hDeviceWindow = m_wndHandle;
	pp.Windowed = TRUE;
	pp.EnableAutoDepthStencil = true;
	pp.AutoDepthStencilFormat = D3DFMT_D24S8;
	pp.Flags = 0;
	pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	//// TW Labtop Set
	////pp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;


	DxErrorException(
		this->CreateDevice(
			( d3dCreateParam->gdpt == GraphicsDeviceProcessType::kHardware ) ?
					D3DDEVTYPE_HAL : D3DDEVTYPE_REF,
			( d3dCreateParam->gdpt == GraphicsDeviceProcessType::kHardware ) ?
					D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			pp
		)
	);

//	GetD3dDevice( )->SetRenderState( D3DRENDERSTATETYPE::, TRUE );
	GetD3dDevice( )->SetRenderState( D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL_NONE );
	GetD3dDevice( )->SetRenderState( D3DRENDERSTATETYPE::D3DRS_LIGHTING, FALSE );
	GetD3dDevice( )->SetRenderState( D3DRENDERSTATETYPE::D3DRS_ZENABLE, TRUE );

	return true;
}


HRESULT tgon::D3d9Device::CreateDevice( D3DDEVTYPE d3dDeviceType, DWORD d3dBehaviorFlag,
												D3DPRESENT_PARAMETERS& pp )
{
	/*D3DDISPLAYMODEEX displayModeEx;
	displayModeEx.RefreshRate = 60;*/ // I think it will be good If using XML
	
	HRESULT hr;
	hr = m_d3d->CreateDeviceEx( D3DADAPTER_DEFAULT, d3dDeviceType, pp.hDeviceWindow,
							  d3dBehaviorFlag, &pp, NULL, &m_d3dDevice );
	assert( m_d3dDevice );
	
	return hr;
}


void tgon::D3d9Device::BeginDisplay( )
{
	assert( m_d3dDevice.p );

	DxErrorException( GetD3dDevice( )->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
									D3DCOLOR_ARGB( 255, 0, 0, 255 ), 1.0f, 0 ));

	// Render 
	DxErrorException( GetD3dDevice( )->BeginScene( ));
}

void tgon::D3d9Device::EndDisplay( )
{
	DxErrorException( GetD3dDevice( )->EndScene( ));
	DxErrorException( GetD3dDevice( )->Present( NULL, NULL, NULL, NULL ));
}

//
//void tgon::D3d9Device::MakeView( D3DXVECTOR3& eye, D3DXVECTOR3& lookAt, D3DXVECTOR3& up )
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
//void tgon::D3d9Device::DrawLine( const D3DXVECTOR3& p1, const D3DXVECTOR3& p2, DWORD color )
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
//void tgon::D3d9Device::MoveLocalX( float dist )
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
//void tgon::D3d9Device::SetMatrices( )
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
//		Aspect ratio ¡æ http://www.slingmedia.co.kr/object/KB-005350.html */
//	D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI/4, 1.0f, 1.0f, 1000.0f );
//	//D3DXMatrixOrthoLH(&matProj, 1280, 720, 1.0f, 100.0f );
//	m_d3dDevice->SetTransform( D3DTS_PROJECTION, &m_matProj );
//}
//

//bool tgon::tgGraphicsDevice::IsAble( )
//{
//	return false;
//}