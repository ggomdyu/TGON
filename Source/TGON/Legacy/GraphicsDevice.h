/**
 * @filename    GraphicsDevice.h
 * @author      ggomdyu
 * @since       04/03/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#   if TGON_USE_DIRECT3D12
#       include "Direct3D11/D3D12GraphicsDevice.h"
#   elif TGON_USE_VULKAN
#       include "Vulkan/VulkanGraphicsDevice.h"
#   elif TGON_USE_OPENGL
#       include "OpenGL/OpenGLGraphicsDevice.h"
#   else
#       include "Direct3D12/D3D11GraphicsDevice.h"
#   endif
#elif BOOST_OS_MACOS
#   include "Metal/MetalGraphicsDevice.h"
#elif BOOST_OS_ANDROID
#elif BOOST_OS_IOS
#endif
