/**
 * @filename    OpenGLContextFwd.h
 * @author      ggomdyu
 * @since       12/29/2017
 */

#pragma once
#include "Core/Platform/Config.h"

#if TGON_PLATFORM_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#       include <Windows.h>
#   endif
#elif TGON_PLATFORM_MACOS
@class NSOpenGLPixelFormat;
@class NSOpenGLContext;
#endif

namespace tgon
{
namespace core
{

class GenericWindow;

} /* namespace core */

namespace graphics
{

struct VideoMode;

} /* namespace graphics */
} /* namespace tgon */
