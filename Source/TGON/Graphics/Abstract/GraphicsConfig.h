/**
 * @filename    GraphicsResource.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief
 */

#pragma once
#include "GenericGraphics.h"

#include <memory>

namespace tgon
{
namespace graphics
{

class GraphicsResource
{
public:
    GraphicsResource(const std::shared_ptr<GenericGraphics>& graphics) :
        m_graphics(graphics)
    {
    }

protected:
    std::shared_ptr<GenericGraphics> m_graphics;
};

} /* namespace graphics */
} /* namespace tgon */
