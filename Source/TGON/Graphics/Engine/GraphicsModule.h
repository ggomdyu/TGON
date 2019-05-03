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
    GraphicsModule(const std::shared_ptr<Window>& window, const VideoMode& videoMode);

/**@section Public destructor */
public:
    virtual ~GraphicsModule() override final = default;
    
/**@section Public method */
public:
    /**@brief   Updates this module. */
    virtual void Update() override;
    const View& GetView() const noexcept;
    View& GetView() noexcept;
    const Graphics& GetGraphics() const noexcept;
    Graphics& GetGraphics() noexcept;

/**@section Private method */
private:
    /**@brief   Draws the render stage. */
    void Draw();

/**@section Private variable */
public:
    Graphics m_graphics;
    View m_view;
};

} /* namespace tgon */
