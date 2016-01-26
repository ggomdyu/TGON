/*
* 작성자 : 차준호
* 작성일 : 2016-01-17
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <string>
#include "D3d9Device.h"


#if defined( _UNICODE ) || defined( UNICODE )
	#define DxErrorException( f )	\
		tgon::dxerr::DxErrorExceptionW( f, __FILEW__, __FUNCTIONW__, __LINE__ )

	#define DxErrorException( f )	\
		tgon::dxerr::DxErrorExceptionW( f, __FILEW__, __FUNCTIONW__, __LINE__ )
#else
	#error "TGON_DirectX support Unicode character sets only."
#endif


namespace tgon
{
	namespace dxerr
	{
		void DxErrorExceptionW( HRESULT hr, LPCWSTR fileName, LPCWSTR funcName, int line );
		void DxErrorAssertionW( HRESULT hr, LPCWSTR fileName, LPCWSTR funcName, int line );
	}

	namespace dxgraphics
	{
		const SpD3d9Effect		LoadShader( const SpD3d9DeviceEx& device, const wchar_t* shaderPath );
		const SpD3d9Mesh		LoadMesh( const SpD3d9DeviceEx& device, const wchar_t* meshPath );
		const SpD3d9Texture	LoadTexture( const SpD3d9DeviceEx& device, const wchar_t* texturePath );
	}
}