#include "stdafx.h"
#include "D3d9Device.h"

#include <cassert>
#include "D3d9Util.h"


tgon::D3d9Device::D3d9Device( const tgon::Window::TWindow& rWindow, const GraphicsDeviceCreateParam& gdcp ) :
	m_wndHandle( rWindow.GetWindowHandle( ))
{
	assert( rWindow.GetWindowHandle( ) != NULL );

	this->Setup( gdcp );
}

tgon::D3d9Device::D3d9Device( const tgon::Window::SpTWindow& pWindow, const GraphicsDeviceCreateParam& gdcp ) :
	m_wndHandle( pWindow->GetWindowHandle( ))
{
	assert( pWindow.get( ));
	assert( pWindow->GetWindowHandle( ) != NULL );

	this->Setup( gdcp );
}

tgon::D3d9Device::~D3d9Device( )
{
	
}


bool tgon::D3d9Device::Setup( const GraphicsDeviceCreateParam& gdcp )
{
	DxErrorException( Direct3DCreate9Ex( D3D_SDK_VERSION, &m_d3d ));
	assert( m_d3d.p );


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

	//// TW Laptop Set
	////pp.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;

	D3DDEVTYPE d3dDevType = ( gdcp.gdpt == GraphicsDeviceProcessType::kHardware ) ?
			D3DDEVTYPE_HAL : D3DDEVTYPE_REF;

	DWORD d3dBehaviorFlag = ( gdcp.gdpt == GraphicsDeviceProcessType::kHardware ) ?
							D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	DxErrorException( this->CreateDevice( d3dDevType, d3dBehaviorFlag, pp ));
	this->SetDefRenderState( );

	return true;
}

void tgon::D3d9Device::SetDefRenderState( )
{
	GetD3dDevice( )->SetRenderState( D3DRENDERSTATETYPE::D3DRS_CULLMODE, D3DCULL_NONE );
	GetD3dDevice( )->SetRenderState( D3DRENDERSTATETYPE::D3DRS_LIGHTING, FALSE );
	GetD3dDevice( )->SetRenderState( D3DRENDERSTATETYPE::D3DRS_ZENABLE, TRUE );
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