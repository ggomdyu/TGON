/**
 * @filename    GraphicsModule.h
 * @author      ggomdyu
 * @since       07/24/2016
 */

#pragma once
#include "IModule.h"

#include <memory>

namespace tgon
{

class GenericWindow;
class GenericGraphics;
struct VideoMode;

class TGON_API GraphicsModule :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(GraphicsModule)

/* @section Public constructor */
public:
    GraphicsModule(const VideoMode& videoMode, const std::shared_ptr<GenericWindow>& window);
    virtual ~GraphicsModule() override;

/* @section Public method */
public:
    virtual void Update() override;

    const std::shared_ptr<GenericGraphics>& GetGraphics() const;

private:
    std::shared_ptr<GenericGraphics> MakeGraphics(const VideoMode& videoMode, const std::shared_ptr<GenericWindow>& window) const;

/* @section Private variable */
private:
    std::shared_ptr<GenericGraphics> m_graphics;
};

} /* namespace tgon */