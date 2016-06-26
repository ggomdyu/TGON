#pragma once
#include "../../../Platform/Utility/Windows/shared_comptr.h"


using SpD3d9Ex = tgon::shared_comptr<struct IDirect3D9Ex>;
using SpD3d9DeviceEx = tgon::shared_comptr<struct IDirect3DDevice9Ex>;
using SpD3d9Sprite = tgon::shared_comptr<struct ID3DXSprite>;
using SpD3d9VertexBuffer = tgon::shared_comptr<struct IDirect3DVertexBuffer9>;
using SpD3d9Effect = tgon::shared_comptr<struct ID3DXEffect>;
using SpD3d9Mesh = tgon::shared_comptr<struct ID3DXMesh>;
using SpD3d9Texture = tgon::shared_comptr<struct IDirect3DTexture9>;