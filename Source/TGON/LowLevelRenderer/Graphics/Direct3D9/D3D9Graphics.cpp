#include "PrecompiledHeader.h"
#include "D3d9Graphics.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "D3D9Error.h"

#pragma comment( lib, "d3d9.lib" )

#if defined( _DEBUG ) || \
	defined( DEBUG )
#	pragma comment( lib, "d3dx9d.lib" )
#else
#	pragma comment( lib, "d3dx9.lib" )
#endif



tgon::D3D9Graphics::D3D9Graphics( const TWindow& owner ) :
	m_deviceCaps( new D3DCAPS9 ),
	m_ownerWindow( owner ),
	m_clearColor( 0x0000ff )
{
	this->InitD3DInterface( );
	this->InitD3DDevice( );
}

bool tgon::D3D9Graphics::Clear( )
{
	HRESULT result = m_d3dDevice->Clear(
		0,
		nullptr,
		D3DCLEAR_TARGET |
		D3DCLEAR_ZBUFFER,
		m_clearColor,
		1.f,
		0 
	);

	if ( SUCCEEDED( result ))
	{
		return true;
	}
	else
	{
		DxTraceW( __FUNCTIONW__, __FILEW__, __LINE__, result, true );
		return false;
	}
}

bool tgon::D3D9Graphics::BeginScene( )
{
	if ( SUCCEEDED( m_d3dDevice->Clear( 
		0, 
		nullptr, 
		D3DCLEAR_TARGET | 
		D3DCLEAR_ZBUFFER,
		m_clearColor, 
		1.f, 
		0 )))
	{
		HRESULT result = m_d3dDevice->BeginScene( );
		if ( SUCCEEDED( result ))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

void tgon::D3D9Graphics::EndScene( )
{
	m_d3dDevice->EndScene( );
	m_d3dDevice->Present( nullptr, nullptr, nullptr, nullptr );
}

void tgon::D3D9Graphics::InitD3DInterface( )
{
	// Initialize direct3D interface.
	V( Direct3DCreate9Ex( D3D_SDK_VERSION, &m_d3d ));

	// Get the device caps from direct3D interface.
	// This structure describes in relation to hardware support.
	V( m_d3d->GetDeviceCaps( D3DADAPTER_DEFAULT, D3DDEVTYPE::D3DDEVTYPE_HAL,
		m_deviceCaps.get( )));
}

void tgon::D3D9Graphics::InitD3DDevice( )
{
	DWORD behaviorFlag = ( m_deviceCaps->DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) ?
		D3DCREATE_HARDWARE_VERTEXPROCESSING :
		D3DCREATE_SOFTWARE_VERTEXPROCESSING;


	D3DPRESENT_PARAMETERS pp {0};
	pp.Windowed = TRUE;
	pp.SwapEffect = D3DSWAPEFFECT::D3DSWAPEFFECT_DISCARD;
	pp.BackBufferCount = 1;
	pp.BackBufferFormat = D3DFORMAT::D3DFMT_UNKNOWN; // D3DFMT_A8R8G8B8
	pp.EnableAutoDepthStencil = TRUE;
	pp.AutoDepthStencilFormat = D3DFORMAT::D3DFMT_D16; // D3DFMT_D24S8
	pp.MultiSampleType = D3DMULTISAMPLE_NONE;
	pp.MultiSampleQuality = 0;
	pp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;


	// Create direct3D device
	V( m_d3d->CreateDeviceEx( 
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE::D3DDEVTYPE_HAL,
		m_ownerWindow.GetWindowHandle( ), 
		behaviorFlag,
		&pp, 
		nullptr, 
		&m_d3dDevice
	))
}