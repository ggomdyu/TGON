#include "PrecompiledHeader.h"
#include "D3D9Graphics.h"

#include <SDL2/include/SDL.h>

tgon::D3D9Graphics::D3D9Graphics( 
	const TWindow& window, 
	const GraphicsStyle& grpStyle )
{
	int n = SDL_Init( SDL_INIT_VIDEO | 
					  SDL_INIT_AUDIO | 
					  SDL_INIT_GAMECONTROLLER | 
					  SDL_INIT_JOYSTICK | 
					  SDL_INIT_NOPARACHUTE );

	this->InitD3D( );
	this->InitD3DDevice( window, grpStyle );
}

tgon::D3D9Graphics::~D3D9Graphics( )
{
}

void tgon::D3D9Graphics::InitD3D( )
{
 	HRESULT hr;
 	V( Direct3DCreate9Ex( D3D_SDK_VERSION, &m_d3d ));
	
	V( m_d3d->GetDeviceCaps( 
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE::D3DDEVTYPE_HAL, 
		&m_d3dCaps ));
}


void tgon::D3D9Graphics::InitD3DDevice( 
	const TWindow& window, 
	const GraphicsStyle& grpStyle )
{
	HRESULT hr;

	// Fill the parameter for device which will make
 	D3DPRESENT_PARAMETERS pp {0};
 	pp.BackBufferWidth = 600;
 	pp.BackBufferHeight = 600;
 	pp.BackBufferFormat = D3DFORMAT::D3DFMT_UNKNOWN;
	pp.BackBufferCount = 1;
	pp.MultiSampleType = D3DMULTISAMPLE_TYPE::D3DMULTISAMPLE_NONE;
	pp.MultiSampleQuality = 0;
	pp.SwapEffect = D3DSWAPEFFECT::D3DSWAPEFFECT_DISCARD;
 	pp.hDeviceWindow = window.GetWindowHandle( );
 	pp.Windowed = ( grpStyle.isWindowed ) ? TRUE : FALSE;
 	pp.EnableAutoDepthStencil = TRUE;
	pp.AutoDepthStencilFormat = D3DFORMAT::D3DFMT_D16; // D24X8
	pp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
	pp.FullScreen_RefreshRateInHz = 0;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	// Set the flags for device's behavior
	DWORD behaviorFlags = 0;
	behaviorFlags |= ( m_d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ) ?
		D3DCREATE_HARDWARE_VERTEXPROCESSING :
		D3DCREATE_SOFTWARE_VERTEXPROCESSING;
 
 	// Create device
	V( m_d3d->CreateDeviceEx(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE::D3DDEVTYPE_HAL,
		window.GetWindowHandle( ),
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&pp,
		nullptr,
		&m_d3dDevice )
	);
}

void tgon::D3D9Graphics::Draw(
	PrimitiveType primitiveType, 
	int32_t startVertex, 
	int32_t primitiveCount )
{
}

void tgon::D3D9Graphics::Draw( 
	PrimitiveType primitiveType, 
	int32_t indexStart, 
	int32_t indexCount, 
	int32_t minVertex, 
	int32_t vertexCount )
{
}