#pragma once
#include <atlbase.h>
#include "../../../Platform/Misc/Windows/shared_comptr.h"
#include <d3d9.h>


struct IDirect3D9Ex;
struct IDirect3DDevice9Ex;
struct ID3DXSprite;
struct IDirect3DVertexBuffer9;
struct ID3DXEffect;
struct ID3DXMesh;
struct IDirect3DTexture9;

using SpD3d9Ex = tgon::shared_comptr<IDirect3D9Ex>;
using SpD3d9DeviceEx = CComPtr<IDirect3DDevice9Ex>;
using SpD3d9Sprite = CComPtr<ID3DXSprite>;
using SpVertexBuffer = CComPtr<IDirect3DVertexBuffer9>;
using SpD3d9Effect = CComPtr<ID3DXEffect>;
using SpD3d9Mesh = CComPtr<ID3DXMesh>;
using SpD3d9Texture = CComPtr<IDirect3DTexture9>;