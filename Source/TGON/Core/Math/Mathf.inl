/*
* Author : Cha Junho
* Date : 03/14/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "Mathf.h"

#include <cmath>


namespace tgon
{


BOOST_FORCEINLINE float Math::Round( float val )
{
	return static_cast<float>( RoundToInt( val ));
}

BOOST_FORCEINLINE int32_t Math::RoundToInt( float val )
{
#if TGON_SUPPORT_SSE
	return _mm_cvt_ss2si( _mm_set_ss( val+val+0.5f )) >> 1;
#else
	return static_cast<int32_t>( std::round( val ));
#endif
}

BOOST_FORCEINLINE float Math::Floor( float val )
{
	return static_cast<float>( FloorToInt( val ));
}

BOOST_FORCEINLINE int32_t Math::FloorToInt( float val )
{
#if TGON_SUPPORT_SSE
	return ( _mm_cvt_ss2si( _mm_set_ss( val+val-0.5f )) >> 1 );
#else
	return static_cast<int32_t>( std::floor( val ));
#endif
}

BOOST_FORCEINLINE float Math::Sqrt( float val )
{
	return std::sqrt( val );
}

template <class Ty>
constexpr Ty Math::Max( Ty first, Ty second )
{
	return ( first >= second ) ? first : second;
}

template <class Ty>
constexpr Ty Math::Min( Ty first, Ty second )
{
	return ( first <= second ) ? first : second;
}

template <class Ty>
constexpr Ty Math::Abs( Ty value )
{
	return ( value < (Ty)(0)) ? -value : value;
}

template<class Ty>
inline constexpr Ty Math::Sign( Ty value )
{
	return ( value > (Ty)(0)) ? (Ty)(1) : ( value < (Ty)(0)) ? (Ty)(-1) : (Ty)(0);
}

template <class Ty>
constexpr Ty Math::Clamp( Ty value, Ty min, Ty max )
{
	return Math::Max( Math::Min( value, max ), min );
}

BOOST_FORCEINLINE uint32_t Math::StringToHash( const char* str )
{
	return x65599Hash( str, std::strlen( str ));
}

BOOST_FORCEINLINE uint32_t Math::StringToHash( const char* str, int length )
{
	return x65599Hash( str, length );
}

constexpr float Math::Lerp( float from, float to, float t )
{
	return from + (( to-from )*t );
}

inline float Math::Smoothstep( float from, float to, float t )
{
	t = Math::Clamp(( t-from )/( to-from ), 0.f, 1.f );

	return t*t*( 3.f-( 2.f*t ));
}

inline Vector3 Math::Hermite( 
	/*IN*/ const Vector3& a,
	/*IN*/ const Vector3& b,
	/*IN*/ const Vector3& c, 
	float t )
{
	const float inv = 1.f - t;
	return {( inv*inv*a ) + ( 2*t*inv*b ) + ( t*t*c )};
}


} /*namespace tgon*/
