#pragma once
#include <string>

#include <d3d9.h>
#include <d3dx9.h>
#include "GraphicsDeviceMisc.h"


namespace tgon
{
	typedef std::wstring DxErrString;

	void GetDXErrorString( HRESULT hr, _Out_ DxErrString* desc );
}