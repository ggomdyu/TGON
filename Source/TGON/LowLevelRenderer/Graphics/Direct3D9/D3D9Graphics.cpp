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



tgon::D3D9Graphics::D3D9Graphics( )
{
	
}

tgon::D3D9Graphics::~D3D9Graphics( )
{
}

void tgon::D3D9Graphics::InitDevice( )
{
	/*HRESULT result = Direct3DCreate9Ex( D3D_SDK_VERSION, &m_d3d );
	if ( FAILED( result ))
	{
		std::wstring errString = std::wstring( L"Failed to initialize Direct3D." ) + 
			GetErrorString( result );

		MessageBox(
			GetFocus( ),
			errString.c_str( ),
			L"WARNING!",
			MB_OK | MB_ICONEXCLAMATION
		);
	}*/
}