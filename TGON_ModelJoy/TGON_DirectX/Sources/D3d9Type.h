#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <atlbase.h>


typedef		CComPtr<IDirect3D9Ex>					SpD3d9Ex;
typedef		CComPtr<IDirect3DDevice9Ex>		SpD3d9DeviceEx;
typedef		CComPtr<IDirect3DVertexBuffer9>	SpVertexBuffer;
typedef		CComPtr<ID3DXEffect>					SpD3d9Effect;
typedef		CComPtr<ID3DXMesh>					SpD3d9Mesh;
typedef		CComPtr<IDirect3DTexture9>			SpD3d9Texture;