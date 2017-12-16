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

} /* namespace platform */

namespace rhi
{

std::unique_ptr<class BaseRHI> MakeRHI(const std::shared_ptr<platform::Window>& window, const struct VideoMode& videoMode);

} /* namespace rhi */
} /* namespace tgon */
