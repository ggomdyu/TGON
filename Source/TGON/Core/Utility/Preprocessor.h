/**
 * @filename    Preprocessor.h
 * @author      ggomdyu
 * @since       04/09/2017
 */

#pragma once
#include <boost/predef.h>
#include <boost/config.hpp>
#include <type_traits>

#ifndef _MSC_VER
#   define TGON_CPP98 199711L
#   define TGON_CPP11 201103L
#   define TGON_CPP14 201300L
#   define TGON_CPP17 201703L

#   define TGON_SUPPORT_CPP98 __cplusplus >= TGON_CPP98
#   define TGON_SUPPORT_CPP11 __cplusplus >= TGON_CPP11
#   define TGON_SUPPORT_CPP14 __cplusplus >= TGON_CPP14
#   define TGON_SUPPORT_CPP17 __cplusplus >= TGON_CPP17
#else

#endif

#if __cplusplus >= TGON_SUPPORT_CPP17
#   define TGON_CONSTEXPR_ON_CPP17 constexpr
#else
#   define TGON_CONSTEXPR_ON_CPP17
#endif

#if __cplusplus > TGON_SUPPORT_CPP17
#   define TGON_CONSTEXPR_ON_CPP20 constexpr
#else
#   define TGON_CONSTEXPR_ON_CPP20
#endif