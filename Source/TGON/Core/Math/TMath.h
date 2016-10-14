/*
* Author : Cha Junho
* Date : 03/14/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Platform/OSAL/PlatformInclude.h"
#include "Vector3.h"

#include <cmath>
#include <cstdint>
#include <boost/config/suffix.hpp>


namespace tgon
{


class TGON_API Math
{
	/* 
	 * Ctor/Dtor
	*/ 
public:
	Math( ) = delete;
	~Math( ) = delete;

	/* 
	 * Commands
	*/ 
public:
	static float Round( float val );
	static int32_t RoundToInt( float val );

	/* @return	Discarded fractional parts */
	static float Floor( float val );

	/* @return	Discarded fractional parts */
	static int32_t FloorToInt( float val );

	/* @return	Square root value */
	static float Sqrt( float value );

	/* @return	Maximum value between first and second */
	template <class Ty>
	static constexpr Ty Max( Ty first, Ty second );

	/* @return	Minimum value between first and second */
	template <class Ty>
	static constexpr Ty Min( Ty first, Ty second );

	/* @return	Absolute value */
	template <class Ty>
	static constexpr Ty Abs( Ty value );

	/* @return	If value is over 0, then 1, else it's below, then -1, else 0 */
	template<class Ty>
	static constexpr Ty Sign( Ty value );

	/* @return	Clamped value between min and max */
	template <class Ty>
	static constexpr Ty Clamp( Ty value, Ty min, Ty max );

	/* 
	 * @param	str		Undecayed string ( e.g. "Text" )
	 * @return			x65599 Hash value
	*/
	template <std::size_t N>
	static uint32_t StringToHash( const char( &str )[N] );
	
	/* 
	 * @param	str		Decayed string ( e.g. const char* = "Text"; )
	 * @return			x65599 x65599 Hash value
	*/
	static uint32_t StringToHash( const char* str, std::size_t length );

	/* 
	 * @param	from	Interpolation start value
	 * @param	to		Interpolation end value
	 * @param	t		Elapsed time
	 * @return			Smoothly interpolated value 
	*/
	static constexpr float Lerp( float from, float to, float t );
	static float Smoothstep( float from, float to, float t );
	
	/* 
	 * @param	a/b/c	Interpolate target
	 * @param	t		Elapsed time
	 * @return			Smoothly interpolated value between three vector
	*/
	static Vector3 Bezier( const Vector3& a, const Vector3& b, const Vector3& c, float t );

	/*
	 *  Variables
	*/
private:
	/* TODO: Pls Do Collision check!! */
	static uint32_t x65599Hash( const char* str, std::size_t length );
public:
	static constexpr float PI = 3.141592654f;
	static constexpr float EPSILON = 0.0001f;
	static constexpr float Deg2Rad = PI / 180;
	static constexpr float Rad2Deg = 180 / PI;
};



BOOST_FORCEINLINE float Math::Round( 
	float val )
{
	return static_cast<float>( RoundToInt( val ));
}

BOOST_FORCEINLINE int32_t Math::RoundToInt(
	float val )
{
//#if TGON_SUPPORT_SSE2
//	return _mm_cvt_ss2si( _mm_set_ss( val+val+0.5f )) >> 1;
//#else
	return static_cast<int32_t>( std::round( val ));
//#endif
}

BOOST_FORCEINLINE float Math::Floor( 
	float val )
{
	return static_cast<float>( FloorToInt( val ));
}

BOOST_FORCEINLINE int32_t Math::FloorToInt( 
	float val )
{
//#if TGON_SUPPORT_SSE2
//	return ( _mm_cvt_ss2si( _mm_set_ss( val+val-0.5f )) >> 1 );
//#else
	return static_cast<int32_t>( std::floor( val ));
//#endif
}

BOOST_FORCEINLINE float Math::Sqrt( 
	float val )
{
	return std::sqrt( val );
}

template <class Ty>
constexpr Ty Math::Max(
	Ty first, 
	Ty second )
{
	return ( first >= second ) ? first : second;
}

template <class Ty>
constexpr Ty Math::Min( 
	Ty first, 
	Ty second )
{
	return ( first <= second ) ? first : second;
}

template <class Ty>
constexpr Ty Math::Abs( 
	Ty value )
{
	return ( value < (Ty)(0)) ? -value : value;
}

template<class Ty>
constexpr Ty Math::Sign( 
	Ty value )
{
	return ( value > (Ty)(0)) ? (Ty)(1) : ( value < (Ty)(0)) ? (Ty)(-1) : (Ty)(0);
}

template <class Ty>
constexpr Ty Math::Clamp( 
	Ty value, 
	Ty min, 
	Ty max )
{
	return Math::Max( Math::Min( value, max ), min );
}

template<std::size_t N>
BOOST_FORCEINLINE uint32_t Math::StringToHash( 
	/*IN*/ const char( &str )[N] )
{
	return x65599Hash( str, N );
}

BOOST_FORCEINLINE uint32_t Math::StringToHash( 
	/*IN*/ const char* str, 
	std::size_t length )
{
	return x65599Hash( str, length );
}

constexpr float Math::Lerp( 
	float from, 
	float to, 
	float t )
{
	return from + (( to-from )*t );
}

inline float Math::Smoothstep( 
	float from, 
	float to, 
	float t )
{
	t = Math::Clamp(( t-from )/( to-from ), 0.f, 1.f );
	return t*t*( 3.f-( 2.f*t ));
}

inline Vector3 Math::Bezier( 
	/*IN*/ const Vector3& a,
	/*IN*/ const Vector3& b,
	/*IN*/ const Vector3& c, 
	float t )
{
	const float inv = 1.f - t;
	return {( inv*inv*a ) + ( 2*t*inv*b ) + ( t*t*c )};
}

BOOST_FORCEINLINE uint32_t Math::x65599Hash( 
	/*IN*/ const char* str, 
	std::size_t length )
{
	uint32_t hash = 0;
	for ( uint32_t i = 0; i < length; ++i )
	{
		hash = 65599*hash + str[i];
	}

	return hash^( hash >> 16 );
}

} /* namespace tgon */