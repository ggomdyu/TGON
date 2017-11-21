/**
 * @filename    GraphicsApplication.h
 * @author      ggomdyu
 * @since       10/21/2017
 */

#pragma once
#include "Core/Platform/Application.h"

#include "GraphicsWindow.h"
#include "GraphicsApplicationFwd.h"

namespace tgon
{
namespace platform
{

class TGON_API GraphicsApplication :
    public Application
{
/* @section Public constructor */
public:
    using Application::Application;
    
    GraphicsApplication(const WindowStyle& windowStyle, const rhi::VideoMode& videoMode);

/* @section Public method */
public:
    virtual void OnDraw() override;

    std::shared_ptr<rhi::BaseRHI>& GetRHI()
    {
        return m_rhi;
    }

/* @section Private method */
private:
    // TODO: Move to Utility.h
    std::shared_ptr<rhi::BaseRHI> MakeRHI(const rhi::VideoMode& videoMode) const;

private:
    std::shared_ptr<rhi::BaseRHI> m_rhi;
};

} /* namespace platform */
} /* namespace tgon */
