/**
 * @filename    TGraphicsDevice.h
 * @author   ggomdyu
 * since    04/03/2016
 */

#pragma once
#include <boost/predef.h>

#define TGON_FORCE_TO_DIRECTX9 1
//#define TGON_FORCE_TO_DIRECTX11 1
//#define TGON_FORCE_TO_DIRECTX12 1
//#define TGON_FORCE_TO_VULKAN 1

#if BOOST_OS_WINDOWS
#	include <sdkddkver.h>
/* @brief   Select DX9 if Windows version is XP or under */
#	if (WINVER <= 0x0501) || (_WIN32_WINNT <= 0x0501) || TGON_FORCE_TO_DIRECTX9
#		define TGON_GRAPHICS_DIRECT3D9 1
#       include "Private/Direct3D9/D3D9GraphicsDevice.h"
#	else
#		define TGON_FORCE_TO_VULKAN 1
#       include "Private/Vulkan/VulkanGraphicsDevice.h"
#	endif
#elif BOOST_OS_ANDROID
#	define TGON_FORCE_TO_VULKAN 1
#elif BOOST_OS_IOS
#endif