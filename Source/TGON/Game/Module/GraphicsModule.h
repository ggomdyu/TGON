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
namespace core
{

class GenericWindow;

} /* namespace core */

namespace graphics
{

class GenericGraphics;
struct VideoMode;

} /* namespace graphics */

namespace game
{

class TGON_API GraphicsModule :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(GraphicsModule)

/* @section Public constructor */
public:
    GraphicsModule(const graphics::VideoMode& videoMode, const std::shared_ptr<core::GenericWindow>& window);
    virtual ~GraphicsModule() override;

/* @section Public method */
public:
    virtual void Update() override;

    const std::unique_ptr<graphics::GenericGraphics>& GetGraphics() const;

private:
    std::unique_ptr<graphics::GenericGraphics> MakeGraphics(const graphics::VideoMode& videoMode, const std::shared_ptr<core::GenericWindow>& window) const;

/* @section Private variable */
private:
    std::unique_ptr<graphics::GenericGraphics> m_graphics;
};

} /* namespace game */
} /* namespace tgon */
