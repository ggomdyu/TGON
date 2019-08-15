#include "PrecompiledHeader.h"

#include "RenderTarget.h"

namespace tgon
{

RenderTarget::RenderTarget(const FExtent2D& extent, int32_t depthBits) :
    RenderTarget(extent.width, extent.height, depthBits)
{
}

}
