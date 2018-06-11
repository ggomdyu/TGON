/**
 * @filename    OpenGLContextFwd.h
 * @author      ggomdyu
 * @since       12/29/2017
 */

#pragma once
#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN 1
#   endif
#   include <Windows.h>
#elif TGON_PLATFORM_MACOS
@class NSOpenGLPixelFormat;
@class NSOpenGLContext;
#endif

namespace tgon
{

struct VideoMode;

} /* namespace tgon */
