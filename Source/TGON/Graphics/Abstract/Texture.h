/**
 * @filename    Texture.h
 * @author      ggomdyu
 * @since       02/20/2018
 * @brief
 */

#pragma once

#if TGON_USING_OPENGL
#   include "OpenGL/OpenGLTexture.h"
#elif TGON_USING_DIRECT3D11
#   include "Direct3D11/D3D11Texture.h"
#elif TGON_USING_DIRECT3D12
#   include "Direct3D12/D3D12Texture.h"
#elif TGON_USING_VULKAN
#   include "Vulkan/VulkanTexture.h"
#endif
