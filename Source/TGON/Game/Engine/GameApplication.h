/**
 * @filename    Engine.h
 * @author      ggomdyu
 * @since       10/21/2017
 */

#pragma once
#include "Core/Platform/Application.h"

namespace tgon
{
namespace platform
{

struct WindowStyle;

} /* namespace platform */

namespace rhi
{

struct VideoMode;
class IDynamicRHI;

} /* namespace rhi */

namespace engine
{

class TGON_API GameApplication :
    public platform::Application
{
/* @section Public constructor */
public:
    GameApplication(const platform::WindowStyle& windowStyle);
    GameApplication(const platform::WindowStyle& windowStyle, const rhi::VideoMode& videoMode);
    virtual ~GameApplication() = default;

/* @section Public method */
public:
    void Update();

    /**
     * @brief   Adds a module to engine.
     *          Added module will be updated automatically by engine.
     */
    template <typename _ModuleType>
    void AddModule(std::unique_ptr<_ModuleType>&& module);

    /**
     * @brief                   Finds a module.
     * @tparam  _ModuleType     Type of module to find
     * @return                  Returns unique-pointer of module if succeeded, nullptr otherwise.
     */
    template <typename _ModuleType>
    const std::unique_ptr<_ModuleType>& FindModule() const;

    const std::unique_ptr<rhi::IDynamicRHI>& GetRHI() const
    {
        return m_rhi;
    }

/* @section Private method */
private:

/* @section Private variable */
private:
    std::unique_ptr<rhi::IDynamicRHI> m_rhi;

//    std::vector<IModule> m_modules;
//    std::unique_ptr<graphics::render::Renderer> m_renderer;
//    std::unique_ptr<gui::module::GUIModule> m_guiModule;
//    std::unique_ptr<game::scene::SceneModule> m_sceneModule;;
};

} /* namespace engine */
} /* namespace tgon */
