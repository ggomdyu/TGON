/**
 * @filename    Prefix.h
 * @author      ggomdyu
 * @since       03/14/2016
 * @brief       Set of Compiler compatible prefix.
 * @seealso     http://www.boost.org/doc/libs/1_64_0/libs/config/doc/html/boost_config/boost_macro_reference.html#boost_config.boost_macro_reference.macros_that_describe_c__11_features_not_supported
 */

#pragma once
#include <boost/predef/compiler.h>

/* @brief   Prefix for TLS */
#ifndef TGON_THREAD_LOCAL
#	if BOOST_COMP_MSVC_DETECTION
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

/* @brief   Prefix for novtable */
#ifndef TGON_NOVTABLE
#   ifdef BOOST_COMP_MSVC_DETECTION
#   	define TGON_NOVTABLE __declspec(novtable)
#   else
#       define TGON_NOVTABLE
#   endif
#endif

/* @brief   Prefix for deprecated */
#ifndef TGON_DEPRECATED
#   if __cplusplus > 199711L
#		define TGON_DEPRECATED(message) [[deprecated(#message)]]
#   else
#   	if BOOST_COMP_MSVC_DETECTION
#   		define TGON_DEPRECATED(message) __declspec(deprecated(a))
#   	elif BOOST_COMP_GNUC_DETECTION
#   		define TGON_DEPRECATED(message) __attribute__((__deprecated__))
#   	else
#   		define TGON_DEPRECATED(message)
#   	endif
#   endif
#endif

/* @brief   Prefix for cdecl */
#ifndef TGON_CDECL
#   if BOOST_COMP_MSVC_DETECTION
#      define TGON_CDECL __cdecl
#   elif BOOST_COMP_GNUC_DETECTION
#      define TGON_CDECL __attribute__((__cdecl__))
#   endif
#endif

#ifndef TGON_RESTRICT
#   if BOOST_COMP_MSVC_DETECTION
#       define TGON_RESTRICT __restrict
#   else
#       define TGON_RESTRICT restrict
#   endif
#endif