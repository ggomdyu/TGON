/**
 * @file    Prefix.h
 * @author  ggomdyu
 * @since   03/14/2016
 * @brief   Set of the compiler-agnostic prefix.
 */

#pragma once

#ifndef TGON_THREAD_LOCAL
#	if TGON_COMPILER_MSVC
#		if (_MSC_VER >= 1900)
#			define TGON_THREAD_LOCAL thread_local
#		else
#			define TGON_THREAD_LOCAL static __declspec(thread)
#		endif
#   elif (__cplusplus >= 201103L)
#		define TGON_THREAD_LOCAL thread_local
#   else
#       define TGON_THREAD_LOCAL
#	endif
#endif

#ifndef TGON_NOVTABLE
#   ifdef TGON_COMPILER_MSVC
#   	define TGON_NOVTABLE __declspec(novtable)
#   else
#       define TGON_NOVTABLE
#   endif
#endif

#ifndef TGON_DEPRECATED
#   if __cplusplus > 199711L
#		define TGON_DEPRECATED(message) [[deprecated(#message)]]
#   else
#   	if TGON_COMPILER_MSVC
#   		define TGON_DEPRECATED(message) __declspec(deprecated(a))
#   	elif TGON_COMPILER_GNUC
#   		define TGON_DEPRECATED(message) __attribute__((__deprecated__))
#   	else
#   		define TGON_DEPRECATED(message)
#   	endif
#   endif
#endif

#ifndef TGON_CDECL
#   if TGON_COMPILER_MSVC
#      define TGON_CDECL __cdecl
#   elif TGON_COMPILER_GNUC
#      define TGON_CDECL __attribute__((__cdecl__))
#   endif
#endif

#ifndef TGON_RESTRICT
#   if TGON_COMPILER_MSVC
#       define TGON_RESTRICT __restrict
#   else
#       define TGON_RESTRICT restrict
#   endif
#endif

#if (DEBUG | !NDEBUG)
#   define TGON_CONDITIONAL_CONSTEXPR
#else
#   define TGON_CONDITIONAL_CONSTEXPR constexpr
#endif
