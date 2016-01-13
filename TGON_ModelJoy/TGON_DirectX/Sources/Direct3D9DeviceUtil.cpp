#include "stdafx.h"
#include "Direct3D9DeviceUtil.h"

#include "IGraphicsDeviceImpl.h"
#include <DxErr.h>

#pragma comment( lib, "DxErr.lib" )


const tgon::D3dDeviceCreateParam tgon::ConvertCreateParamToD3dType( const GraphicsDeviceCreateParam& gdcp )
{
	D3dDeviceCreateParam d3dCreateParam;

	d3dCreateParam.d3dDeviceType = ( gdcp.gdpt == GraphicsDeviceProcessType::kHardware ) ?
		D3DDEVTYPE_HAL : D3DDEVTYPE_REF;

	d3dCreateParam.d3dBehaviorFlag = ( gdcp.gdpt == GraphicsDeviceProcessType::kHardware ) ?
		D3DCREATE_HARDWARE_VERTEXPROCESSING :
			D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	d3dCreateParam.presentWnd = gdcp.presentWnd;
	d3dCreateParam.width = gdcp.width;
	d3dCreateParam.height = gdcp.height;
	d3dCreateParam.isFullWindow = gdcp.isFullWindow;

	return d3dCreateParam;
}


#if defined( _DEBUG ) | defined( DEBUG )

tgon::DxErrString* tgon::DXErrorString( HRESULT hr, const wchar_t* srcFile, unsigned int line )
{
	static wchar_t errMsg[1000];


	if ( FAILED( hr ))
	{
		LPCTSTR errDesc = DXGetErrorDescriptionW( hr );
		LPCTSTR errString = DXGetErrorStringW( hr );
	
		// Assemble
		// DX9 Invoke Error :  Some invalid pointer [NONE_ARGS]
		// C:\\someDir, 342 lines
		wsprintf( errMsg,	L"DX9 Invoke Error : %s [%s]\n\
								%s, %d lines", errDesc, errString, srcFile, line );

		return errMsg;
	}
	
	return nullptr;
}

#else
const wchar_t* tgon::DXErrorString( HRESULT hr )
{
	static wchar_t errMsg[1000];


	if ( FAILED( hr ))
	{
		LPCTSTR errDesc = DXGetErrorDescriptionW( hr );
		LPCTSTR errString = DXGetErrorStringW( hr );
	
		// Assemble
		// DX9 Invoke Error :  Some invalid pointer [NONE_ARGS]
		// C:\\someDir, 342 lines
		wsprintf( errMsg,	L"DX9 Invoke Error : %s [%s]", errDesc, errString );
	}

	return errMsg;
}
#endif
