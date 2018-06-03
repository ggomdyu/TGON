/**
 * @filename    MacOSConfig.h
 * @author      ggomdyu
 * @since       07/16/2017
 * @brief       The set of platform specific configurations.
 */

#pragma once

#define TGON_PLATFORM_NAME MacOS
#define TGON_PLATFORM_MACOS 1
#define TGON_USING_LITTLE_ENDIAN 1
#define TGON_SUPPORT_SSE
#define TGON_SUPPORT_SSE2
#define TGON_SUPPORT_SIMD TGON_SUPPORT_SSE || TGON_SUPPORT_SSE2
#define TGON_USING_SIMD TGON_SUPPORT_SIMD
#define TGON_API
