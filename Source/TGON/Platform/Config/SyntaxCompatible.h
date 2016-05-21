/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description : Make compatible the syntax of C++ to lower version compiler.
*/


#pragma once
#include "Compiler.h"
#include <boost/config.hpp>


// constexpr
// @Description : boost/config.hpp( 1.60.0 ) does not support constexpr exactly
#ifdef TGON_COMPILER_MSVC // Using Visual Studio?
	#if ( _MSC_VER >= 1900 ) // VS2015 or better?
		#define TGON_CONSTEXPR constexpr 
		#define TGON_CONSTEXPR_OR_CONST constexpr
		#define TGON_CONSTEXPR_OR_INLINE constexpr
	#else
		#define TGON_CONSTEXPR
		#define TGON_CONSTEXPR_OR_CONST const
		#define TGON_CONSTEXPR_OR_INLINE inline
	#endif
#else // Other compiler
	#define TGON_CONSTEXPR BOOST_CONSTEXPR
	#define TGON_CONSTEXPR_OR_CONST BOOST_CONSTEXPR_OR_CONST
#endif


// TLS
#ifdef TGON_COMPILER_MSVC // Using Visual Studio?
	#if ( _MSC_VER >= 1900 )
		#define TGON_THREAD_LOCAL thread_local
	#else
		#define TGON_THREAD_LOCAL static __declspec( thread )
	#endif
#else
	#define TGON_THREAD_LOCAL thread_local
#endif


// Novtable
#ifdef TGON_COMPILER_MSVC
	#define TGON_NOVTABLE __declspec( novtable )
#else
	#define TGON_NOVTABLE
#endif