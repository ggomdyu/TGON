/*
* Author : Cha Junho
* Date : 04/01/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <boost/predef/os.h>

#if BOOST_OS_WINDOWS
#	include "../Windows/WindowsInclude.h"
#	include "../Windows/WindowsConfig.h"
#endif

#ifndef TGON_SUPPORT_SSE2
#   define TGON_SUPPORT_SSE 0
#endif
#ifndef TGON_SUPPORT_NEON
#   define TGON_SUPPORT_NEON 0
#endif
#ifndef TGON_SUPPORT_SIMD
#   define TGON_SUPPORT_SIMD 0
#endif