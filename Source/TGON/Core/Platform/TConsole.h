/**
 * filename TConsole.h
 * author   ggomdyu
 * since    07/06/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Private/Windows/WindowsConsole.h"
#endif