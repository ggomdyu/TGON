/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include "Engine/IModule.h"
#include "Graphics/Graphics.h"
#include "Graphics/MeshRenderer.h"
#include "Graphics/UI/UIRenderer.h"

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
    UIRenderer& GetUIRenderer() noexcept;
    MeshRenderer& GetMeshRenderer() noexcept;
    const Graphics& GetGraphics() const noexcept;
    const UIRenderer& GetUIRenderer() const noexcept;
    const MeshRenderer& GetMeshRenderer() const noexcept;
    
/**@section Method */
private:
    void Draw();

/**@section Variable */
public:
    Graphics m_graphics;
    UIRenderer m_uiRenderer;
    MeshRenderer m_meshRenderer;
};

} /* namespace tgon */
