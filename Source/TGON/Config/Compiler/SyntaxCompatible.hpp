/*
* 작성자 : 차준호
* 작성일 : 2016-03-14
* 최종 수정 :
* 최종 수정일 :
* Description : Make compatible the syntax of C++ to lower version compilers that are supported in upper.
*/


#pragma once
#include "../Platform/Platform.h"
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
		#define TGON_STATIC_CONSTEXPR_VALUE( type, name, value )\
			static constexpr type name = value;
		#define TGON_STATIC_CONSTEXPR_VALUE_IMPL( name, value )
	#else
		#define TGON_CONSTEXPR
		#define TGON_CONSTEXPR_OR_CONST const
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
#ifdef BOOST_MSVC // Using Visual Studio?
	#if ( BOOST_MSVC >= 1900 )
		#define TGON_THREAD_LOCAL thread_local
	#else
		#define TGON_THREAD_LOCAL static __declspec( thread )
	#endif
#elif defined( BOOST_GCC ) // Using gcc?
	#define TGON_THREAD_LOCAL __thread
#else
	#define TGON_THREAD_LOCAL
#endif


/*
	inline
*/
#define TGON_FORCEINLINE BOOST_FORCEINLINE
#define TGON_NOINLINE BOOST_NOINLINE


/*
	Alignment
*/
#define TGON_ALIGNMENT( byte ) BOOST_ALIGNMENT( byte )
