#pragma once
#include <string>

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

	const D3dDeviceCreateParam ConvertCreateParamToD3dType( const GraphicsDeviceCreateParam& );


	typedef std::wstring DxErrString;
	void GetDXErrorString( HRESULT hr, _Out_ DxErrString* desc );
}