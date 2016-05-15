/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description : Make compatible the syntax of C++ to lower version compilers that are supported in upper.
*/


#pragma once
#include "Compiler.h"
#include <boost/config.hpp>


/*
	noexcept
*/
#define TGON_NOEXCEPT_OR_NOTHROW BOOST_NOEXCEPT_OR_NOTHROW
#define TGON_NOEXCEPT BOOST_NOEXCEPT
#define TGON_NOEXCEPT_IF(Predicate) BOOST_NOEXCEPT_IF(Predicate)
#define TGON_NOEXCEPT_EXPR(Expression) BOOST_NOEXCEPT_EXPR(Expression)


/*
	constexpr
	@Description : boost/config.hpp( 1.60.0 ) does not support constexpr exactly
*/
#ifdef _MSC_VER // Using Visual Studio?
	#if ( _MSC_VER >= 1900 ) // VS2015 or better?
		#define TGON_CONSTEXPR constexpr 
		#define TGON_CONSTEXPR_OR_CONST constexpr
		#define TGON_CONSTEXPR_OR_INLINE constexpr
		#define TGON_STATIC_CONSTEXPR_VALUE( type, name, value )\
			static constexpr type name = value;
		#define TGON_STATIC_CONSTEXPR_VALUE_IMPL( name, value )
	#else
		#define TGON_CONSTEXPR
		#define TGON_CONSTEXPR_OR_CONST const
		#define TGON_CONSTEXPR_OR_INLINE inline
		#define TGON_STATIC_CONSTEXPR_VALUE( type, name, value )\
			static const type name;
		#define TGON_STATIC_CONSTEXPR_VALUE_IMPL( name, value )\
			decltype( name ) name = value;
	#endif
#else // Other compiler
	#define TGON_CONSTEXPR BOOST_CONSTEXPR
	#define TGON_CONSTEXPR_OR_CONST BOOST_CONSTEXPR_OR_CONST
#endif


/*
	TLS ( Thread local storage )
*/
#ifdef TGON_COMPILER_MSVC // Using Visual Studio?
	#if ( _MSC_VER >= 1900 )
		#define TGON_THREAD_LOCAL thread_local
	#else
		#define TGON_THREAD_LOCAL static __declspec( thread )
	#endif
#else
	#define TGON_THREAD_LOCAL thread_local
#endif


/*
	inline
*/
#ifdef TGON_COMPILER_MSVC
	#define TGON_FORCEINLINE __forceinline
#elif defined( TGON_COMPILER_GNUC )
	#define TGON_FORCEINLINE __attribute__(( always_inline ))
#else
	#define TGON_FORCEINLINE inline
#endif


/*
	Alignment
*/
#define TGON_ALIGNMENT( byte ) BOOST_ALIGNMENT( byte )
