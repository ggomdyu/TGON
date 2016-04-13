/*
* Author : Junho-Cha
* Date : 2016-03-14
* Latest author :
* Latest date :
* Description :
*/


#pragma once
#include "../Platform/Platform.h"


#if defined( _MSC_VER ) || defined( _MSC_FULL_VER ) || defined( _MSC_VER )
	#define TGON_COMPILER_MSVC

#elif defined( __llvm__ )
	#define TGON_COMPILER_LLVM

#elif defined( __GNUC__ ) || defined( __GNUC_MINOR__ ) ||\
	  defined( __GNUC_PATCHLEVEL__ )
	#define TGON_COMPILER_GNUC

#elif defined( __clang__ ) || defined( __clang_major__ ) ||\
	  defined( __clang_minor__ ) || defined( __clang_patchlevel__ )
	#define TGON_COMPILER_CLANG
#endif