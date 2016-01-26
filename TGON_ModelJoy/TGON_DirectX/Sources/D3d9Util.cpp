#include "stdafx.h"
#include "D3d9Util.h"

#include <iostream>
#include <DxErr.h>

#pragma comment( lib, "DxErr.lib" )


void GetDxErrorString( HRESULT hr, _Out_ std::wstring* desc,
								   LPCWSTR fileName,
								   LPCWSTR funcName,
								   int line )
{
	assert( FAILED( hr ));

	LPCWSTR errDesc = DXGetErrorDescriptionW( hr );
	LPCWSTR errString = DXGetErrorStringW( hr );
	
	/*
		¡Ø Assemble ex

		DX Invoke Error : Some invalid pointer [NONE_ARGS]
		[Function] : dxerr::dxgraphics::foo
		[File] : C:\Users\User\My
		[Line] : 32 lines
	*/

	*desc = L"DX Invoke Error : ";
	*desc += errDesc;
	*desc += L" [";
	*desc += errString;
	*desc += L"]\n";

	*desc += L"[Function] : ";
	*desc += funcName;
	*desc += L"\n";

	*desc += L"[Files] : ";
	*desc += fileName;
	*desc += L"\n";

	*desc += L"[Line] : ";
	*desc += std::to_wstring( line );
	*desc += L" lines\n";
}


void tgon::dxerr::DxErrorExceptionW( HRESULT hr, LPCWSTR fileName, LPCWSTR funcName, int line )
{
	if ( FAILED( hr ))
	{
		std::wstring errString;
		GetDxErrorString( hr, &errString, fileName, funcName, line );

		MessageBoxW( GetFocus( ), errString.c_str( ), L"WARNING!",
					 MB_OK | MB_ICONEXCLAMATION );
		abort( );
	}
}


void tgon::dxerr::DxErrorAssertionW( HRESULT hr, LPCWSTR fileName, LPCWSTR funcName, int line )
{
#if defined( _DEBUG ) | defined( DEBUG )
	DxErrorExceptionW( hr, fileName, funcName, line );
#endif
}


const SpD3d9Effect tgon::dxgraphics::LoadShader( const SpD3d9DeviceEx& device, const wchar_t* shaderPath )
{
	SpD3d9Effect retShader = nullptr;
	LPD3DXBUFFER errBuffer = nullptr;
	DWORD shaderFlag = 0;

#if defined( _DEBUG ) | defined( DEBUG )
	shaderFlag |= D3DXSHADER_DEBUG;
#endif

	HRESULT hr = D3DXCreateEffectFromFileW( device, shaderPath,
			nullptr,			// #define definition to use when compiling the shader
			nullptr,			// ? 
			shaderFlag,
			nullptr,			// ?
			&retShader,
			&errBuffer );

	if ( FAILED( hr ))
	{
		std::wstring errString = L"DX Invoke Error : Failed to load shader. [";
		errString += shaderPath;
		errString += L']';

		MessageBoxW( GetFocus( ), errString.c_str( ), L"MB_OK", MB_OK );
	}

	if ( errBuffer && !retShader )
	{
		int size = errBuffer->GetBufferSize( );
		void* errMsg = errBuffer->GetBufferPointer( );

		if ( errMsg )
		{
			MessageBoxA( GetFocus( ), static_cast<const char*>( errMsg ), "WARNING!",
						MB_OK );
		}
	}

	return retShader;
}

const SpD3d9Mesh tgon::dxgraphics::LoadMesh( const SpD3d9DeviceEx& device, const wchar_t* meshPath )
{
	SpD3d9Mesh retMesh = nullptr;

	DxErrorException(
		D3DXLoadMeshFromXW( meshPath,
				D3DXMESH_SYSTEMMEM,
				device,
				nullptr,		// I think it's useless
				nullptr,		// Material
				nullptr,		// Effect instance?
				nullptr,		// Material count
				&retMesh )
	);

	return retMesh;
}


const SpD3d9Texture tgon::dxgraphics::LoadTexture( const SpD3d9DeviceEx& device, const wchar_t* texturePath )
{
	SpD3d9Texture retTexture = nullptr;

	if ( FAILED( D3DXCreateTextureFromFileW( device, texturePath, &retTexture )))
	{
		std::wstring errString = L"DX Invoke Error : Failed to load texture. [";
		errString += texturePath;
		errString += L']';

		MessageBoxW( GetFocus( ), errString.c_str( ), L"WARNING!", MB_OK );
	}

	return retTexture;
}