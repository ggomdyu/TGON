/**
 * filename TApplication.h
 * author   ggomdyu
 * since    04/01/2016
 */

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "Private/Windows/WindowsApplication.h"
#endif