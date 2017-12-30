/**
 * @filename    RHIUtility.h
 * @author      ggomdyu
 * @since       10/22/2017
 */

#pragma once
#include <memory>

namespace tgon
{
namespace platform
{

class Window;
struct VideoMode;

} /* namespace platform */

namespace rhi
{

class IDynamicRHI;

std::unique_ptr<IDynamicRHI> MakeRHI(const std::shared_ptr<platform::Window>& window, const VideoMode& videoMode);

} /* namespace rhi */
} /* namespace tgon */