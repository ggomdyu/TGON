/**
 * filename D3D9GraphicsDevice.h
 * author   ggomdyu
 * since    04/02/2017
 */

#pragma once
#include "../Interface/IGraphicsDevice.h"

#include "./Core/Platform/Private/Windows/Misc/UniqueComPtr.h"
#include "./Core/Platform/Private/Windows/Misc/SharedComPtr.h"
#include "./RenderCore/Device/Private/Direct3D9/D3D9GraphicsInstance.h"

#include <d3d9.h>
#include <d3dx9.h>

namespace tgon
{

class D3D9Renderer :
    public GenericRenderer<D3D9Renderer>
{
/**
 * @section Ctor/Dtor
 */
public:
    using GenericRenderer::GenericRenderer;
    virtual ~D3D9Renderer();

/**
 * @section Public commands
 */
public:
    virtual void Clear() override;
    virtual void BeginScene() override;
    virtual void EndScene() override;
    virtual void Present() override;

/**
 * @section Event handler
 */
public:
    void OnLostDevice();
    void OnResetDevice();
    void OnWindowResized();

/**
 * @section Get methods
 */
public:

/**
 * @section Get methods
 */
private:
    UniqueComPtr<IDirect3DDevice9Ex> m_d3dDevice;
};

using TRenderer = D3D9Renderer;

} /* namespace tgon */