/*
* Author : Cha Junho
* Date : 04/24/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <boost/predef/os.h>


#if !BOOST_OS_WINDOWS
#   error "WindowsPlatformConfig.h included but BOOST_WINDOWS is not defined"
#endif

/*
	Dynamic-link library
*/
#ifndef TGON_STATIC_BUILD
#	ifdef TGON_API_EXPORT
#		define TGON_API __declspec( dllexport )
#	else
#		define TGON_API __declspec( dllimport )
#	endif
#else
/*
	Staic library
*/
#	define TGON_API
#endif