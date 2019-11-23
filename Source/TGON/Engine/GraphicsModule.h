/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include "Graphics/Graphics.h"
#include "UI/UIRenderer.h"

#include "Module.h"

namespace tgon
{

class GraphicsModule :
    public Module
{
public:
    TGON_DECLARE_RTTI(GraphicsModule)
    
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
    const Graphics& GetGraphics() const noexcept;
    UIRenderer& GetUIRenderer() noexcept;
    const UIRenderer& GetUIRenderer() const noexcept;
    
/**@section Method */
private:
    void Draw();

/**@section Variable */
public:
    Graphics m_graphics;
    UIRenderer m_uiRenderer;
};

} /* namespace tgon */
