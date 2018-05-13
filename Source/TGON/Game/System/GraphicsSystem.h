/**
 * @filename    GraphicsSystem.h
 * @author      ggomdyu
 * @since       07/24/2016
 */

#pragma once
#include "ISystem.h"

#include "Graphics/LowLevelRender/Graphics.h"

namespace tgon
{

class TGON_API GraphicsSystem final :
	public ISystem
{
public:
    TGON_RUNTIME_OBJECT(GraphicsSystem)

/* @section Public constructor */
public:
    GraphicsSystem(const VideoMode& videoMode, const std::shared_ptr<GenericWindow>& window);

/* @section Public destructor */
public:
    virtual ~GraphicsSystem() final override;

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