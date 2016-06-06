/*
* Author : Junho-Cha
* Date : 01/17/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <d3dx9.h>


#if defined( DEBUG ) || defined( _DEBUG )
#	ifndef V
#		define V(x) { hr = (x); /*assert( hr == S_OK );*/ }
#	endif
#	ifndef V_RETURN
#		define V_RETURN(x) { hr = (x); if ( FAILED( hr )) { return tgon::DxTraceW( __FILEW__, __LINE__, hr, L#x, true ); }}
#	endif
#else
#	ifndef V6
#		define V(x) { hr = (x); }
#	endif
#	ifndef V_RETURN
#		define V_RETURN(x) { hr = (x); if ( FAILED( hr )) { return hr; }}
#	endif
#endif


namespace tgon
{


UINT D3d9GetColorChannelBits( const D3DFORMAT fmt );
UINT D3d9GetDepthBits( const D3DFORMAT fmt );
UINT D3d9GetStencilBits( const D3DFORMAT fmt );

std::wstring GetDXErrorString( const wchar_t* fileName,
							   uint32_t line,
							   HRESULT result );

void DxTraceW( const wchar_t* fileName,
			   uint32_t line,
			   HRESULT result,
			   const wchar_t* msg,
			   bool popMsgBox );

//// lapper
//SpD3d9Effect LoadShader( const SpD3d9DeviceEx&,
//						 const wchar_t* shaderPath );

//SpD3d9Mesh LoadMesh( const SpD3d9DeviceEx&,
//					 const wchar_t* meshPath );

//SpD3d9Texture LoadTexture( const SpD3d9DeviceEx&,
//						   const wchar_t* texturePath );



//// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//bool IsDeviceAcceptable( IDirect3D9Ex* d3dInterface,
//						 D3DCAPS9* pCaps,
//						 D3DFORMAT AdapterFormat,
//						 D3DFORMAT BackBufferFormat );


}