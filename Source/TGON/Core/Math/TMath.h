/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "TVector3.h"
#include "../../Platform/Slate/PlatformProperty.h"
#include "../../Platform/Config/Build.h"


#define PI 3.141592654f
#define EPSILON 0.0001f


namespace tgon
{


class TGON_API TMath
{
public:
	TGON_CONSTEXPR static float Deg2Rad( float degree );
	TGON_CONSTEXPR static float Rad2Deg( float radian );

	static float Round( float val );
	static int32_t RoundToInt( float val );
	static float Floor( float val );
	static int32_t FloorToInt( float val );
	static float Sqrt( float value );
	TGON_CONSTEXPR static float Max( float first, float second );
	TGON_CONSTEXPR static float Min( float first, float second );
	TGON_CONSTEXPR static float Abs( float value );
	TGON_CONSTEXPR static float Clamp( float value, float min, float max );


	/*
		Hashing
	*/
	BOOST_FORCEINLINE static uint32_t GenerateHash( const char* str );


	/*
		Interpolation
	*/
	TGON_CONSTEXPR static float Lerp( float from, float to, float t );
	static float Smoothstep( float from, float to, float t );
	static TVector3 Hermite( const TVector3& a, const TVector3& b, const TVector3& c, float t );


private:
	// x65599 Hasher
	static uint32_t x65599Hash( const char* str, size_t length );
};


TGON_CONSTEXPR_OR_INLINE float TMath::Deg2Rad(
	float angle ) 
{
	return angle*( PI/180.f );
}

TGON_CONSTEXPR_OR_INLINE float TMath::Rad2Deg(
		float radian ) 
{
	return radian*( 180.f/PI );
}

BOOST_FORCEINLINE float tgon::TMath::Round(
	float val ) 
{
	return static_cast<float>( RoundToInt( val ));
}

BOOST_FORCEINLINE int32_t tgon::TMath::RoundToInt(
	float val ) 
{
#if TGON_SUPPORT_SSE
	return _mm_cvt_ss2si( _mm_set_ss( val+val+0.5f )) >> 1;
#else
	return std::round( val );
#endif
}

BOOST_FORCEINLINE float tgon::TMath::Floor(
	float val ) 
{
	return static_cast<float>( FloorToInt( val ));
}

BOOST_FORCEINLINE int32_t tgon::TMath::FloorToInt(
	float val ) 
{
#if TGON_SUPPORT_SSE
	return ( _mm_cvt_ss2si( _mm_set_ss( val+val-0.5f )) >> 1 );
#else
	return std::floor( val );
#endif
}

TGON_CONSTEXPR float TMath::Lerp(
	float from,
	float to,
	float t ) 
{
	return from + (( to-from )*t );
}

inline float tgon::TMath::Smoothstep(
	float from,
	float to,
	float t ) 
{
	const float _t = 
		TMath::Clamp(( t-from )/( to-from ),
								   0.0f,
								   1.0f );
	return _t*_t*( 3-2*_t );
}

inline TVector3 TMath::Hermite(
	const TVector3& a,
	const TVector3& b,
	const TVector3& c,
	float t )
{
	return {(( 1-t )*( 1-t )*a ) +
			( 2*t*( 1-t )*b ) +
			( t*t*c )};
}

TGON_CONSTEXPR_OR_INLINE float TMath::Max(
	float first,
	float second )
{
	return ( first >= second ) ? first : second;
}

TGON_CONSTEXPR_OR_INLINE float TMath::Min(
	float first, 
	float second )
{
	return ( first <= second ) ? first : second;
}

TGON_CONSTEXPR_OR_INLINE float TMath::Abs(
	float value )
{
	return ( value < 0 ) ? -value : value;
}

TGON_CONSTEXPR_OR_INLINE float tgon::TMath::Clamp(
	float value, float min, float max ) 
{
	return TMath::Max(
		TMath::Min( value, max ),
		min
	);
}

BOOST_FORCEINLINE float tgon::TMath::Sqrt(
	float value )
{
	return std::sqrt( value );
}

BOOST_FORCEINLINE uint32_t TMath::GenerateHash(
	const char* str )
{
	return x65599Hash( str, std::strlen( str ));
}


}