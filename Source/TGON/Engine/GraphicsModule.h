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
    GraphicsModule(Window& window, const VideoMode& videoMode);

/**@section Method */
public:
    Graphics& GetGraphics() noexcept;
    const Graphics& GetGraphics() const noexcept;
    UIRenderer& GetUIRenderer() noexcept;
    const UIRenderer& GetUIRenderer() const noexcept;
    void Update() override;
    
/**@section Method */
private:
    void Draw();
    void OnResizeWindow(int32_t width, int32_t height);
    
/**@section Variable */
private:
    Graphics m_graphics;
    UIRenderer m_uiRenderer;
};

} /* namespace tgon */
