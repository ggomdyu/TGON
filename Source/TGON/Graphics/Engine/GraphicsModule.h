/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   12/31/2017
 */

#pragma once
#include "Core/Engine/IModule.h"

#include "../LowLevel/Graphics.h"
#include "../Render/RenderStage.h"

namespace tgon
{
    
class TGON_API GraphicsModule :
    public IModule
{
public:
    TGON_RUNTIME_OBJECT(GraphicsModule);
    
/**@section Public constructor */
public:
    GraphicsModule(Window& window, const VideoMode& videoMode);

/**@section Public destructor */
public:
    virtual ~GraphicsModule() override = default;
    
/**@section Public method */
public:
    /**@brief   Updates the module. */
    virtual void Update() override;
    
    /**@brief   Gets the Graphics. */
    Graphics& GetGraphics() noexcept;
    
    /**@brief   Gets the Graphics. */
    const Graphics& GetGraphics() const noexcept;
    
    /**@brief   Gets the RenderStage. */
    RenderStage& GetRenderStage() noexcept;
    
    /**@brief   Gets the RenderStage. */
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
