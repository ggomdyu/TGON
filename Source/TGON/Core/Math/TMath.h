/*
* Author : Cha Junho
* Date : 03/14/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Platform/PlatformInclude.h"
#include "Vector3.h"

#include <cstdint>
#include <cmath>
#include <boost/config/suffix.hpp>


namespace tgon
{


class TGON_API TMath
{
	// 
	// Static variables
	// 
public:
	static constexpr float PI = 3.141592654f;
	static constexpr float EPSILON = 0.0001f;
	static constexpr float Deg2Rad = PI/180;
	static constexpr float Rad2Deg = 180/PI;

	// 
	// Commands
	// 
public:
	static float Round( float val );
	static int32_t RoundToInt( float val );
	static float Floor( float val );
	static int32_t FloorToInt( float val );

	// @return Return root of value 
	static float Sqrt( float value );

	/* @return	Return maximum value between first and second */
	template <class Ty>
	static constexpr Ty Max( Ty first, Ty second );

	/* @return	Return minimum value between first and second */
	template <class Ty>
	static constexpr Ty Min( Ty first, Ty second );

	/* @return	Return absolute value of 'value' */
	template <class Ty>
	static constexpr Ty Abs( Ty value );

	/* @return if value is over 0, then return 1, else it's below, then return -1, else return 0 */
	template<class Ty>
	static constexpr Ty Sign( Ty value );

	/* @return	Return clamped value between min and max */
	template <class Ty>
	static constexpr Ty Clamp( Ty value, Ty min, Ty max );

	/* @return	Return x65599 hash key */
	template <std::size_t N>
	static uint32_t StringToHash( const char( &str )[N] );
	static uint32_t StringToHash( const char* str, std::size_t length );

	static constexpr float Lerp( float from, float to, float t );
	static float Smoothstep( float from, float to, float t );
	static Vector3 BezierCurve( const Vector3& a, const Vector3& b, const Vector3& c, float t );

	// 
	// Ctor/Dtor
	// 
public:
	TMath( ) = delete;
	virtual ~TMath( ) = delete;

	//
	//  Private variables
	//
private:
	static uint32_t x65599Hash( const char* str, std::size_t length );
};



BOOST_FORCEINLINE float TMath::Round( 
	float val )
{
	return static_cast<float>( RoundToInt( val ));
}

BOOST_FORCEINLINE int32_t TMath::RoundToInt(
	float val )
{
//#if TGON_SUPPORT_SSE2
//	return _mm_cvt_ss2si( _mm_set_ss( val+val+0.5f )) >> 1;
//#else
	return static_cast<int32_t>( std::round( val ));
//#endif
}

BOOST_FORCEINLINE float TMath::Floor( 
	float val )
{
	return static_cast<float>( FloorToInt( val ));
}

BOOST_FORCEINLINE int32_t TMath::FloorToInt( 
	float val )
{
//#if TGON_SUPPORT_SSE2
//	return ( _mm_cvt_ss2si( _mm_set_ss( val+val-0.5f )) >> 1 );
//#else
	return static_cast<int32_t>( std::floor( val ));
//#endif
}

BOOST_FORCEINLINE float TMath::Sqrt( 
	float val )
{
	return std::sqrt( val );
}

template <class Ty>
constexpr Ty TMath::Max(
	Ty first, 
	Ty second )
{
	return ( first >= second ) ? first : second;
}

template <class Ty>
constexpr Ty TMath::Min( 
	Ty first, 
	Ty second )
{
	return ( first <= second ) ? first : second;
}

template <class Ty>
constexpr Ty TMath::Abs( 
	Ty value )
{
	return ( value < (Ty)(0)) ? -value : value;
}

template<class Ty>
constexpr Ty TMath::Sign( 
	Ty value )
{
	return ( value > (Ty)(0)) ? (Ty)(1) : ( value < (Ty)(0)) ? (Ty)(-1) : (Ty)(0);
}

template <class Ty>
constexpr Ty TMath::Clamp( 
	Ty value, 
	Ty min, 
	Ty max )
{
	return TMath::Max( TMath::Min( value, max ), min );
}

template<std::size_t N>
BOOST_FORCEINLINE uint32_t TMath::StringToHash( 
	/*IN*/ const char( &str )[N] )
{
	return x65599Hash( str, N );
}

BOOST_FORCEINLINE uint32_t TMath::StringToHash( 
	/*IN*/ const char* str, 
	std::size_t length )
{
	return x65599Hash( str, length );
}

BOOST_FORCEINLINE uint32_t TMath::StringToHash( 
	/*IN*/ const char* str, 
	std::size_t length )
{
	return x65599Hash( str, length );
}

constexpr float TMath::Lerp( 
	float from, 
	float to, 
	float t )
{
	return from + (( to-from )*t );
}

inline float TMath::Smoothstep( 
	float from, 
	float to, 
	float t )
{
	t = TMath::Clamp(( t-from )/( to-from ), 0.f, 1.f );
	return t*t*( 3.f-( 2.f*t ));
}

inline Vector3 TMath::BezierCurve( 
	/*IN*/ const Vector3& a,
	/*IN*/ const Vector3& b,
	/*IN*/ const Vector3& c, 
	float t )
{
	const float inv = 1.f - t;
	return {( inv*inv*a ) + ( 2*t*inv*b ) + ( t*t*c )};
}

BOOST_FORCEINLINE uint32_t TMath::x65599Hash( 
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


#include "Mathf.inl"