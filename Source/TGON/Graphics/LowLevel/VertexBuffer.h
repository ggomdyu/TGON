/**
 * @file    VertexBuffer.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once

#if TGON_USING_OPENGL
#   include "OpenGL/OpenGLVertexBuffer.h"
#elif TGON_USING_DIRECT3D11
#   include "Direct3D11/D3D11VertexBuffer.h"
#elif TGON_USING_DIRECT3D12
#   include "Direct3D12/D3D12VertexBuffer.h"
#elif TGON_USING_VULKAN
#   include "Vulkan/VulkanVertexBuffer.h"
#endif
