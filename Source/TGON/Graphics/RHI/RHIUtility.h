/**
 * @filename    RHI.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief
 */

#pragma once
#include <memory>

namespace tgon
{
namespace rhi
{

class BaseRHI;
struct VideoMode;

std::unique_ptr<rhi::BaseRHI> MakeRHI(const rhi::VideoMode& videoMode);

} /* namespace rhi */
} /* namespace tgon */
