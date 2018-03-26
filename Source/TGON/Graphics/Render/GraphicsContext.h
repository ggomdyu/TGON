/**
 * @filename    Texture.h
 * @author      ggomdyu
 * @since       03/15/2018
 * @brief
 */


#pragma once
#include <memory>

#include "../LowLevelRender/Generic/GenericGraphics.h"

namespace tgon
{

class GraphicsContext
{
public:

private:
    std::shared_ptr<GenericGraphics> m_graphics;
};

using SharedGraphicsContext = std::shared_ptr<GenericGraphics>;

} /* namespace tgon */
