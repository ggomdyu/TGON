#pragma once
#include <d3d9.h>
#include "../../../Platform/Misc/Windows/shared_comptr.h"


struct IDirect3D9Ex;
struct IDirect3DDevice9Ex;
struct ID3DXSprite;
struct IDirect3DVertexBuffer9;
struct ID3DXEffect;
struct ID3DXMesh;
struct IDirect3DTexture9;

using SpD3d9Ex = tgon::shared_comptr<IDirect3D9Ex>;
using SpD3d9DeviceEx = tgon::shared_comptr<IDirect3DDevice9Ex>;
using SpD3d9Sprite = tgon::shared_comptr<ID3DXSprite>;
using SpVertexBuffer = tgon::shared_comptr<IDirect3DVertexBuffer9>;
using SpD3d9Effect = tgon::shared_comptr<ID3DXEffect>;
using SpD3d9Mesh = tgon::shared_comptr<ID3DXMesh>;
using SpD3d9Texture = tgon::shared_comptr<IDirect3DTexture9>;