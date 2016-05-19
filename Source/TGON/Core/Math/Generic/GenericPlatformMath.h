/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description :
*/


#pragma once
#include "../TVector3.h"
#include "../../../Platform/Config/Build.h"
#include "../../../Platform/Config/SyntaxCompatible.h"


#define PI 3.141592654f
#define EPSILON 0.0001f


namespace tgon
{
class TGON_API GenericPlatformMath
{
public:
	TGON_CONSTEXPR static float DegreeToRadian( float degree );
	TGON_CONSTEXPR static float RadianToDegree( float radian );

	BOOST_FORCEINLINE static float Sqrt( float value );
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


TGON_CONSTEXPR_OR_INLINE float GenericPlatformMath::DegreeToRadian(
	float angle ) 
{
	return angle*( PI/180.f );
}

TGON_CONSTEXPR_OR_INLINE float GenericPlatformMath::RadianToDegree(
		float radian ) 
{
	return radian*( 180.f/PI );
}

TGON_CONSTEXPR float GenericPlatformMath::Lerp(
	float from,
	float to,
	float t ) 
{
	return from + (( to-from )*t );
}

inline float tgon::GenericPlatformMath::Smoothstep(
	float from,
	float to,
	float t ) 
{
	const float _t = 
		GenericPlatformMath::Clamp(( t-from )/( to-from ),
								   0.0f,
								   1.0f );
	return _t*_t*( 3-2*_t );
}

inline TVector3 GenericPlatformMath::Hermite(
	const TVector3& a,
	const TVector3& b,
	const TVector3& c,
	float t )
{
	return {( std::pow(( 1-t ), 2 )*a ) +
			( 2*t*( 1-t )*b ) +
			( t*t*c )};
}

TGON_CONSTEXPR_OR_INLINE float GenericPlatformMath::Max(
	float first,
	float second )
{
	return ( first >= second ) ? first : second;
}

TGON_CONSTEXPR_OR_INLINE float GenericPlatformMath::Min(
	float first, 
	float second )
{
	return ( first <= second ) ? first : second;
}

TGON_CONSTEXPR_OR_INLINE float GenericPlatformMath::Abs(
	float value )
{
	return ( value < 0 ) ? -value : value;
}

TGON_CONSTEXPR_OR_INLINE float tgon::GenericPlatformMath::Clamp(
	float value, float min, float max ) 
{
	return GenericPlatformMath::Max(
		GenericPlatformMath::Min( value, max ),
		min
	);
}

BOOST_FORCEINLINE float tgon::GenericPlatformMath::Sqrt(
	float value )
{
	return std::sqrt( value );
}

BOOST_FORCEINLINE uint32_t GenericPlatformMath::GenerateHash(
	const char* str )
{
	return x65599Hash( str, std::strlen( str ));
}


}