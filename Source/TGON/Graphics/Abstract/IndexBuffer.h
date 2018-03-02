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
#elif TGON_USING_DIRECT3D12
#   include "Direct3D12/D3D12IndexBuffer.h"
#elif TGON_USING_VULKAN
#   include "Vulkan/VulkanIndexBuffer.h"
#endif
