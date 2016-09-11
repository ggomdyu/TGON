/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description : Make compatible the syntax of C++ to lower version compiler.
*/


#pragma once                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
#include <boost/config/suffix.hpp>


// constexpr
#ifndef TGON_CONSTEXPR
#	define TGON_CONSTEXPR BOOST_CONSTEXPR
#	define TGON_CONSTEXPR_OR_CONST BOOST_CONSTEXPR_OR_CONST
#endif

// TLS
#ifndef TGON_THREAD_LOCAL
#	if _MSC_VER
#		if ( _MSC_VER >= 1900 ) /*vs2015*/
#			define TGON_THREAD_LOCAL thread_local
#		else
#			define TGON_THREAD_LOCAL static __declspec( thread )
#		endif
#	else
#		define TGON_THREAD_LOCAL thread_local
#	endif
#endif


// Novtable
#ifdef TGON_COMPILER_MSVC
#	define TGON_NOVTABLE __declspec( novtable )
#else
#endif


// deprecated
#ifndef TGON_DEPRECATED
#	ifdef _MSC_VER
#		define TGON_DEPRECATED( msg ) __declspec( deprecated( a ))
#	elif defined( __GNUC__ )
#		define TGON_DEPRECATED( msg ) __attribute__(( __deprecated__ ))
#	else
#		define TGON_DEPRECATED( msg )
#	endif
#endif


// noexcept
#ifndef TGON_NOEXCEPT
#	define TGON_NOEXCEPT BOOST_NOEXCEPT
#endif