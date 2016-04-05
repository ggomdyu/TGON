#include "PrecompiledHeader.h"
#include "D3d9Device.h"

#include "../Window/TWindow.h"
#include "Graphics/GraphicsDeviceProp.h"

#include <cassert>
#include <d3d9.h>
#include <d3dx9.h>
#include <atlbase.h>
#include <Windows.h>



tgon::D3d9Device::D3d9Device( const tgon::SpTWindow& window,
							  const GraphicsDeviceProp& gdcp )
{
	this->SetupDevice( window, gdcp );
	this->SetupSpriteDevice( );
}

tgon::D3d9Device::~D3d9Device( )
{
}

void tgon::D3d9Device::BeginDraw( )
{
	HRESULT result;

	//V( m_devImpl.d3dDevice->Clear(
	//		0,
	//		NULL,
	//		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
	//		D3DCOLOR_ARGB( 255, 0, 0, 255 ),
	//		1.0f,
	//		0 )
	//	);

	//V( m_devImpl.d3dDevice->BeginScene( ));
}

void tgon::D3d9Device::EndDraw( )
{
	HRESULT result;
	
	//V( m_devImpl.d3dDevice->EndScene( ));
	//V( m_devImpl.d3dDevice->Present( NULL, NULL, NULL, NULL ));
}

void tgon::D3d9Device::SetupDevice( const tgon::SpTWindow& window,
									const GraphicsDeviceProp& gdcp )
{
	assert( window.get( ) && "Unallocated window passed into parameter.\
			( tgon::D3d9Device::SetupDevice )" );

	HRESULT result;
	//V( Direct3DCreate9Ex( D3D_SDK_VERSION, &m_devImpl.d3d ));


	// Make device caps
	/*V( m_devImpl.d3d->GetDeviceCaps(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE::D3DDEVTYPE_HAL,
			&m_devImpl.deviceCaps
		));*/


	DWORD behaviorFlags = 0;
	if ( m_devImpl.deviceCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
	{
		behaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else
	{
		behaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}


	// Make device
	D3DPRESENT_PARAMETERS pp {0};
	pp.Windowed = ( gdcp.isWindowed ) ? TRUE : FALSE;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD; // Best efficient swap
	pp.BackBufferFormat = D3DFMT_UNKNOWN; // Follow current background's mode
	

	m_devImpl.d3d->CreateDeviceEx(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			window->GetWindowHandle(),
			behaviorFlags,
			&pp,
			nullptr,
			nullptr
		);
}

void tgon::D3d9Device::SetupSpriteDevice( )
{
	//HRESULT result;
	//V( D3DXCreateSprite( m_d3dDevice, &m_d3dSprite ));
}
