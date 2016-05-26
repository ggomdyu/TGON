#include "PrecompiledHeader.h"
#include "D3d9Graphics.h"

#include <cassert>

#include "../../../Platform/Window/TWindow.h"
#include "../GraphicsStyle.h"


tgon::D3d9Graphics::D3d9Graphics(
	const SpTWindow& window, 
	const GraphicsStyle& grpStyle )
{
	this->InitDevice( window, grpStyle );
	this->InitSpriteDevice( );
}


tgon::D3d9Graphics::~D3d9Graphics( )
{
}


void tgon::D3d9Graphics::InitDevice(
	const SpTWindow& window, 
	const GraphicsStyle& grpStyle )
{
	assert( window.get( ) && 
		"Invalid argument passed to tgon::D3d9Graphics::InitDevice." );


	// Create d3d
	HRESULT result;
	V( Direct3DCreate9Ex( D3D_SDK_VERSION, &m_d3d ));
	

	// Set behavior flags
	V( m_d3d->GetDeviceCaps( 
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE::D3DDEVTYPE_HAL, 
		&m_deviceCaps )
	);

	DWORD behaviorFlags = 0;
	if ( m_deviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	{
		behaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		behaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	// Assemble
	D3DPRESENT_PARAMETERS pp {0};
	pp.Windowed = ( grpStyle.isWindowed ) ? TRUE : FALSE;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.BackBufferFormat = D3DFMT_UNKNOWN;
	pp.AutoDepthStencilFormat = D3DFMT_D16;
	pp.EnableAutoDepthStencil = TRUE;
	pp.BackBufferWidth = grpStyle.backBufferWidth;
	pp.BackBufferHeight = grpStyle.backBufferHeight;
	pp.hDeviceWindow = window->GetWindowHandle( );
	

	// Create d3d device
	V( m_d3d->CreateDeviceEx(
		  D3DADAPTER_DEFAULT,
		  D3DDEVTYPE::D3DDEVTYPE_HAL,
		  window->GetWindowHandle(),
		  behaviorFlags,
		  &pp,
		  nullptr,
		  &m_d3dDevice
	));
}


void tgon::D3d9Graphics::InitSpriteDevice( )
{
	HRESULT result;
	V( D3DXCreateSprite( m_d3dDevice, &m_d3dSprite ));
}


void tgon::D3d9Graphics::Draw(
	PrimitiveType primitiveType, 
	int32_t startVertex, 
	int32_t primitiveCount )
{
}

void tgon::D3d9Graphics::Draw( 
	PrimitiveType primitiveType, 
	int32_t indexStart, 
	int32_t indexCount, 
	int32_t minVertex, 
	int32_t vertexCount )
{
	/*m_d3dDevice->DrawIndexedPrimitive(
		pri
	)*/
}
