#pragma once
#include "../Platform/Misc/Windows/shared_comptr.h"

using SpD3D9Ex = tgon::shared_comptr<struct IDirect3D9Ex>;
using SpD3D9DeviceEx = tgon::shared_comptr<struct IDirect3DDevice9Ex>;
using SpD3D9Sprite = tgon::shared_comptr<struct ID3DXSprite>;
using SpD3D9VertexBuffer = tgon::shared_comptr<struct IDirect3DVertexBuffer9>;
using SpD3D9Effect = tgon::shared_comptr<struct ID3DXEffect>;
using SpD3D9Mesh = tgon::shared_comptr<struct ID3DXMesh>;
using SpD3D9Texture = tgon::shared_comptr<struct IDirect3DTexture9>;