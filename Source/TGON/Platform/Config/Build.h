/*
* Author : Cha Junho
* Date : 04/24/2016
* Latest author :
* Latest date :
*/


#pragma once

#ifndef TGON_STATIC_BUILD
#	if BOOST_OS_WINDOWS
#		ifdef TGON_API_EXPORT
#			define TGON_API __declspec( dllexport )
#		else
#			define TGON_API __declspec( dllimport )
#		endif
#	else
#		ifdef ( __GNUC__ >= 4 )
#			define TGON_API __attribute__( __visibility__( "default" ))
#		endif
#	endif
#else
#	define TGON_API
#endif