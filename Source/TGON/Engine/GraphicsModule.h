/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include "Engine/IModule.h"
#include "Graphics/Graphics.h"
#include "Graphics/View.h"
#include "Graphics/SpriteBatch.h"

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
    /**@brief   Updates this module. */
    virtual void Update() override;
    Graphics& GetGraphics() noexcept;
    const Graphics& GetGraphics() const noexcept;
    View& GetView() noexcept;
    const View& GetView() const noexcept;
    
/**@section Method */
private:
    /**@brief   Draws the render stage. */
    void Draw();

/**@section Variable */
public:
    Graphics m_graphics;
    View m_view;
};

} /* namespace tgon */
