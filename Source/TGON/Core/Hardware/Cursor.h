/**
 * @filename    Cursor.h
 * @author      ggomdyu
 * @since       09/01/2017
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Windows/WindowsCursor.h"
#elif BOOST_OS_MACOS
#	include "MacOS/MacOSCursor.h"
#else
#   error "This platform does not support cursor."
#endif
