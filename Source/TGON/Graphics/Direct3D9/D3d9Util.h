/*
* Author : Junho-Cha
* Date : 01/17/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <string>
#include <d3dx9.h>
#include "D3d9Fwd.h"


#if defined( DEBUG ) || defined( _DEBUG )
	#ifndef V
		#define V(x) { result = (x); if ( FAILED( result )) { tgon::DxTraceW( __FILEW__, __LINE__, result, L#x, true ); }}
	#endif
	#ifndef V_RETURN
		#define V_RETURN(x) { result = (x); if ( FAILED( result )) { return tgon::DxTraceW( __FILEW__, __LINE__, result, L#x, true ); }}
	#endif
#else
	#ifndef V6
		#define V(x) { result = (x); }
	#endif
	#ifndef V_RETURN
		#define V_RETURN(x) { result = (x); if ( FAILED( result )) { return result; }}
	#endif
#endif


namespace tgon
{
	// Error
	std::wstring GetDXErrorString(
		LPCWSTR fileName,
		UINT line,
		HRESULT result );

	std::wstring GetDXErrorString( HRESULT result );


	void DxTraceW(
		LPCWSTR fileName,
		UINT line,
		HRESULT result,
		LPCWSTR msg,
		bool popMsgBox );


	// lapper
	SpD3d9Effect LoadShader( const SpD3d9DeviceEx&,
							 const wchar_t* shaderPath );

	SpD3d9Mesh LoadMesh( const SpD3d9DeviceEx&,
						 const wchar_t* meshPath );

	SpD3d9Texture LoadTexture( const SpD3d9DeviceEx&,
							   const wchar_t* texturePath );


	// Utility
	UINT D3d9GetColorChannelBits( const D3DFORMAT fmt );
	UINT D3d9GetDepthBits( const D3DFORMAT fmt );
	UINT D3d9GetStencilBits( const D3DFORMAT fmt );
	

	// Rejects any D3D9 devices that aren't acceptable to the app by returning false
	bool IsDeviceAcceptable( IDirect3D9Ex* d3dInterface,
							 D3DCAPS9* pCaps,
							 D3DFORMAT AdapterFormat,
							 D3DFORMAT BackBufferFormat );
}