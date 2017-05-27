/**
 * @filename    TGraphicsDevice.h
 * @author      ggomdyu
 * @since       04/03/2016
 */

#pragma once

#if TGON_USE_DIRECTX11
#	include "Private/DirectX11/D3DX11Renderer.h"
#elif TGON_USE_DIRECTX12
#	include "Private/DirectX12/D3DX12Renderer.h"
#elif TGON_USE_OPENGL
#	include "Private/OpenGL/OpenGLRenderer.h"
#elif TGON_USE_VULKAN
#	include "Private/Vulkan/VulkanRenderer.h"
#endif