/**
 * @file    Shader.h
 * @author  ggomdyu
 * @since   10/22/2017
 */

#pragma once

#if TGON_USING_OPENGL
#   include "OpenGL/OpenGLShader.h"
#elif TGON_USING_DIRECT3D11
#   include "Direct3D11/D3D11Shader.h"
#elif TGON_USING_DIRECT3D12
#   include "Direct3D12/D3D12Shader.h"
#elif TGON_USING_VULKAN
#   include "Vulkan/VulkanShader.h"
#endif
