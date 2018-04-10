/**
 * @filename    IndexBuffer.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief
 */

#pragma once

#if TGON_USING_OPENGL
#   include "OpenGL/OpenGLIndexBuffer.h"
#elif TGON_USING_DIRECT3D11
#   include "Direct3D11/D3D11IndexBuffer.h"
#elif TGON_USING_VULKAN
#   include "Vulkan/VulkanIndexBuffer.h"
#endif

namespace tgon
{

class IndexBuffer : 
#if TGON_USING_OPENGL
    public OpenGLIndexBuffer
#elif TGON_USING_DIRECT3D11
    public Direct3D11IndexBuffer
#elif TGON_USING_VULKAN
    public VulkanIndexBuffer
#endif
{
/* @section Public constructor */
public:
    using OpenGLIndexBuffer::OpenGLIndexBuffer;
};

} /* namespace tgon */