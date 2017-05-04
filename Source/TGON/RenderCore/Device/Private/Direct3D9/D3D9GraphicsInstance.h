/**
 * @filename    D3D9GraphicsInstance.h
 * @author   ggomdyu
 * since    04/02/2017
 */

#pragma once
#include "../Interface/IGraphicsDevice.h"

#include "Core/Platform/Windows/Misc/UniqueComPtr.h"

#include <d3d9.h>
#include <d3dx9.h>

namespace tgon
{

class D3D9GraphicsInstance :
    public IGraphicsInstance
{
/**
 * @section Ctor/Dtor
 */
public:
    D3D9GraphicsInstance();
    virtual ~D3D9GraphicsInstance();

/**
 * @section Get method
 */
public:
    UniqueComPtr<IDirect3D9Ex>& GetD3D();

private:
    UniqueComPtr<IDirect3D9Ex> m_d3d;
};

}