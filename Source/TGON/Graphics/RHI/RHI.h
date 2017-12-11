/**
 * @filename    RHI.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief
 */

#pragma once
#include <memory>

#include "RHIFwd.h"

namespace tgon
{
namespace rhi
{

std::unique_ptr<BaseRHI> MakeRHI(const std::shared_ptr<platform::Window>& window, const VideoMode& videoMode);

} /* namespace rhi */
} /* namespace tgon */