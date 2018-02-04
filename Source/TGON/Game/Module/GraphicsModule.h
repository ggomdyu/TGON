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
class Window;
}
namespace graphics
{
class IDynamicGraphics;
struct VideoMode;
}

namespace game
{

class TGON_API GraphicsModule :
	public IModule
{
public:
    TGON_RUNTIME_OBJECT(GraphicsModule)

/* @section Public constructor */
public:
    GraphicsModule(const std::shared_ptr<core::Window>& window, const graphics::VideoMode& videoMode);
    virtual ~GraphicsModule() override;

/* @section Public method */
public:
    virtual void Update() override;

    const std::unique_ptr<graphics::IDynamicGraphics>& GetGraphics() const;

private:
    std::unique_ptr<graphics::IDynamicGraphics> MakeGraphics(const std::shared_ptr<core::Window>& window, const graphics::VideoMode& videoMode) const;

/* @section Private variable */
private:
    std::unique_ptr<graphics::IDynamicGraphics> m_graphics;
};

} /* namespace game */
} /* namespace tgon */
