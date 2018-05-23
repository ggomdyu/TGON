/**
 * @filename    GraphicsModule.h
 * @author      ggomdyu
 * @since       07/24/2016
 */

#pragma once
#include "Core/Object/IModule.h"

#include "Graphics/LowLevelRender/Graphics.h"

namespace tgon
{

class TGON_API GraphicsModule final :
	public IModule
{
/* @section Public constructor */
public:
    GraphicsModule(const VideoMode& videoMode, const std::shared_ptr<GenericWindow>& window);

/* @section Public destructor */
public:
    virtual ~GraphicsModule() final override;

/* @section Public method */
public:
    virtual void Update() final override;

    Graphics& GetGraphics();
    const Graphics& GetGraphics() const;

/* @section Public method */
public:
private:
 
/* @section Private variable */
private:
    Graphics m_graphics;
};

} /* namespace tgon */