/*
* Author : Junho-Cha
* Date : 04/24/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "Platform.h"


#ifndef TGON_STATIC_BUILD
	#ifdef TGON_PLATFORM_WINDOWS
		#ifdef TGON_API_EXPORT
			#define TGON_API __declspec( dllexport )
		#else
			#define TGON_API __declspec( dllimport )
		#endif
	#elif TGON_PLATFORM_LINUX
		#ifdef ( __GNUC__ >= 4 )
			#define TGON_API __attribute__( __visibility__( "default" ))
		#endif
	#endif
#else
	#define TGON_API
#endif