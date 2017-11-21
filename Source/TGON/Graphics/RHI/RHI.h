/**
 * @filename    RHI.h
 * @author      ggomdyu
 * @since       10/22/2017
 * @brief
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#elif BOOST_OS_MACOS
#elif BOOST_OS_ANDROID
#elif BOOST_OS_IOS
#endif

#include "OpenGL/OpenGLRHI.h"
