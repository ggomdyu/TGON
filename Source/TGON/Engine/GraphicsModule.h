/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include "Engine/IModule.h"
#include "Graphics/Graphics.h"
#include "Graphics/CanvasRenderer.h"
#include "Graphics/MeshRenderer.h"

namespace tgon
{

class TGON_API GraphicsModule :
    public IModule
{
public:
    TGON_DECLARE_RTTI(GraphicsModule);
    
/**@section Constructor */
public:
    GraphicsModule(const Window& window, const VideoMode& videoMode);

/**@section Destructor */
public:
    virtual ~GraphicsModule() override final = default;
    
/**@section Method */
public:
    virtual void Update() override;
    Graphics& GetGraphics() noexcept;
    CanvasRenderer& GetCanvasRenderer() noexcept;
    MeshRenderer& GetMeshRenderer() noexcept;
    const Graphics& GetGraphics() const noexcept;
    const CanvasRenderer& GetCanvasRenderer() const noexcept;
    const MeshRenderer& GetMeshRenderer() const noexcept;
    
/**@section Method */
private:
    void Draw();

/**@section Variable */
public:
    Graphics m_graphics;
    CanvasRenderer m_canvasRenderer;
    MeshRenderer m_meshRenderer;
};

} /* namespace tgon */
