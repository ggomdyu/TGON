#pragma once

#include <d3d9.h>
#include <d3dx9.h>


struct GraphicsDeviceCreateParam;


namespace tgon
{

	struct D3dDeviceCreateParam
	{
		HWND presentWnd;
		unsigned int width, height;
		bool isFullWindow;

		DWORD d3dBehaviorFlag;
		D3DDEVTYPE d3dDeviceType;


	};
	typedef const wchar_t DxErrString;



	const D3dDeviceCreateParam ConvertCreateParamToD3dType( const GraphicsDeviceCreateParam& );

#if defined( _DEBUG ) | defined( DEBUG )
	// Return nullptr if It has no error
	DxErrString* DXErrorString( HRESULT hr, const wchar_t* srcFile, unsigned int line );
#elif
	DxErrString* DXErrorString( HRESULT hr );
#endif

}