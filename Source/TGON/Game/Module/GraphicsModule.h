/**
 * @filename    IModule.h
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
class IDynamicRHI;
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
    virtual ~GraphicsModule() = default;

/* @section Public method */
public:
    virtual void Update() override;

    const std::unique_ptr<graphics::IDynamicRHI>& GetRHI() const;

private:
    std::unique_ptr<graphics::IDynamicRHI> MakeRHI(const std::shared_ptr<core::Window>& window, const graphics::VideoMode& videoMode) const;

/* @section Private variable */
private:
    std::unique_ptr<graphics::IDynamicRHI> m_rhi;
};

} /* namespace game */
} /* namespace tgon */