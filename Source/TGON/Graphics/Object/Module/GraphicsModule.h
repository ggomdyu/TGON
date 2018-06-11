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
    void Draw();
    
    const SpriteBatch& GetSpriteBatch() const noexcept;
    SpriteBatch& GetSpriteBatch() noexcept;
    const Graphics& GetGraphics() const noexcept;
    Graphics& GetGraphics() noexcept;

/* @section Public method */
private:
 
/* @section Private variable */
private:
    Graphics m_graphics;
    
    SpriteBatch m_spriteBatch;
};

} /* namespace tgon */
