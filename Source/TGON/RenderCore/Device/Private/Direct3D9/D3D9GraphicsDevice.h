/**
 * filename D3D9GraphicsDevice.h
 * author   ggomdyu
 * since    04/02/2017
 */

#pragma once
#include "../Interface/IGraphicsDevice.h"

class D3D9Renderer :
    public IRenderer
{
/**
 * @section Ctor/Dtor
 */
public:
    D3D9Renderer();
    virtual ~D3D9Renderer();

/**
 * @section Public commands
 */
public:
    void BeginScene();
    void EndScene();

/**
 * @section Event handler
 */
public:
    void OnLostDevice();
    void OnResetDevice();
    void OnWindowResized();

/**
 * @section Set methods
 */
public:
    void SetWorldMatrix();
    void SetViewMatrix();
    void SetProjectionMatrix();
    void SetViewProjectionMatrix();

/**
 * @section Get methods
 */
public:

private:
};

using TRenderer = D3D9Renderer;