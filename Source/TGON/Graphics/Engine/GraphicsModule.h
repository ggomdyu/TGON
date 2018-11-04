/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include "Core/Engine/Module/IModule.h"

#include "../LowLevel/Graphics.h"
#include "../Render/View.h"

namespace tgon
{

class TGON_API GraphicsModule :
    public IModule
{
public:
    TGON_DECLARE_RTTI(GraphicsModule);
    
/**@section Public constructor */
public:
    GraphicsModule(Window& window, const VideoMode& videoMode);

/**@section Public destructor */
public:
    virtual ~GraphicsModule() override final = default;
    
/**@section Public method */
public:
    /**@brief   Updates this module. */
    virtual void Update() override;

    //View& GetView() noexcept;

    //const View& GetView() const noexcept;
    
/**@section Private method */
private:
    /**@brief   Draws the render stage. */
    void Draw();

/**@section Private variable */
public:
    Graphics& GetGraphics() noexcept;
    const Graphics& GetGraphics() const noexcept;
    Graphics m_graphics;
    
    //View m_view;
};

} /* namespace tgon */
