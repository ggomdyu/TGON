/**
 * @filename    TGraphicsDevice.h
 * @author      ggomdyu
 * @since       04/03/2016
 */

#pragma once

#if TGON_USE_DIRECT3D11
#	include "Private/Direct3D11/D3D11GraphicsDevice.h"
#elif TGON_USE_DIRECT3D12
#	include "Private/Direct3D12/D3D12GraphicsDevice.h"
#elif TGON_USE_OPENGL
#	include "Private/OpenGL/OpenGLGraphicsDevice.h"
#elif TGON_USE_VULKAN
#	include "Private/Vulkan/VulkanGraphicsDevice.h"
#endif