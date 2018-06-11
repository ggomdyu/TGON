/**
 * @filename    GraphicsModule.h
 * @author      ggomdyu
 * @since       07/24/2016
 */

#pragma once
#include "Core/Object/Module/IModule.h"
#include "Graphics/LowLevel/Graphics.h"
#include "Graphics/Render/SpriteBatch.h"

namespace tgon
{

class TGON_API GraphicsModule final :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(GraphicsModule);

/* @section Public constructor */
public:
    GraphicsModule(const VideoMode& videoMode, Window& displayTargetWindow);

/* @section Public destructor */
public:
    virtual ~GraphicsModule() final override;

/* @section Public method */
public:
    virtual void Update() final override;
    void Draw(GraphicsContext& graphicsContext);

    SpriteBatch& GetSpriteBatch() noexcept;
    const SpriteBatch& GetSpriteBatch() const noexcept;
    Graphics& GetGraphics() noexcept;
    const Graphics& GetGraphics() const noexcept;

/* @section Public method */
private:
 
/* @section Private variable */
private:
    Graphics m_graphics;
    GraphicsContext m_graphicsContext;
    SpriteBatch m_spriteBatch;
};

} /* namespace tgon */
