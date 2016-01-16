#include "stdafx.h"
#include "Direct3D9DeviceUtil.h"

#include "IGraphicsDeviceImpl.h"
#include <iostream>
#include <DxErr.h>

#pragma comment( lib, "DxErr.lib" )

//
//const tgon::D3dDeviceCreateParam tgon::ConvertCreateParamToD3dType( const GraphicsDeviceCreateParam& gdcp )
//{
//	D3dDeviceCreateParam d3dCreateParam;
//
//	d3dCreateParam.d3dDeviceType = ( gdcp.gdpt == GraphicsDeviceProcessType::kHardware ) ?
//		D3DDEVTYPE_HAL : D3DDEVTYPE_REF;
//
//	d3dCreateParam.d3dBehaviorFlag = ( gdcp.gdpt == GraphicsDeviceProcessType::kHardware ) ?
//		D3DCREATE_HARDWARE_VERTEXPROCESSING :
//			D3DCREATE_SOFTWARE_VERTEXPROCESSING;
//
//	d3dCreateParam.presentWnd = static_cast<HWND>( gdcp.wndPtr );
//	d3dCreateParam.width = gdcp.width;
//	d3dCreateParam.height = gdcp.height;
//	d3dCreateParam.isFullWindow = gdcp.isFullWindow;
//
//	return d3dCreateParam;
//}


void tgon::GetDXErrorString( HRESULT hr, _Out_ DxErrString* desc )
{
	if ( FAILED( hr ))
	{
		LPCWSTR errDesc = DXGetErrorDescriptionW( hr );
		LPCWSTR errString = DXGetErrorStringW( hr );
	
		// Assemble ex
		// DX Invoke Error :  Some invalid pointer [NONE_ARGS]
		*desc = L"DX Invoke Error : ";
		*desc += errDesc;
		*desc += L" [";
		*desc += errString;
		*desc += L']';
	}
}