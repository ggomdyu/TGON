/**
 * filename D3D9GraphicsInstance.h
 * author   ggomdyu
 * since    04/02/2017
 */

#pragma once
#include <d3d9.h>
#include <d3dx9.h>

#include "../Interface/IGraphicsInstance.h"

namespace tgon
{

class D3D9GraphicsInstance :
    public IGraphicsInstance
{
public:
    D3D9GraphicsInstance();
    virtual ~D3D9GraphicsInstance();

private:
    IDirect3D9Ex* m_d3d;
};

}