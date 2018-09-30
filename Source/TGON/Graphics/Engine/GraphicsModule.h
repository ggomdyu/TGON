/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include "Core/Engine/Module/IModule.h"

#include "../LowLevel/Graphics.h"
#include "../Render/RenderStage.h"

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
    virtual ~GraphicsModule() override
    {
        int n = 3;
    }
    
/**@section Public method */
public:
    /**@brief   Updates this module. */
    virtual void Update() override;

    Graphics& GetGraphics() noexcept;

    const Graphics& GetGraphics() const noexcept;

    RenderStage& GetRenderStage() noexcept;

    const RenderStage& GetRenderStage() const noexcept;
    
/**@section Private method */
private:
    /**@brief   Draws the render stage. */
    void Draw();

/**@section Private variable */
public:
    Graphics m_graphics;
    
    RenderStage m_renderStage;
};

} /* namespace tgon */
