#include "PrecompiledHeader.h"
#include "D3d9Graphics.h"


tgon::D3d9Graphics::D3d9Graphics( )
{
	HRESULT hr = Direct3DCreate9Ex( D3D_SDK_VERSION, &m_d3d );
	if ( FAILED( hr ))
	{
		MessageBox(
			GetFocus( ),
			L"Failed to invoke Direct3DCreate9Ex.",
			L"WARNING!",
			MB_OK | MB_ICONEXCLAMATION
		);
	}
}

tgon::D3d9Graphics::~D3d9Graphics( )
{
}