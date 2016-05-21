/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description :
*/


#pragma once
#include "../TVector3.h"
#include "../../../Platform/Config/BuildOption.h"
#include "../../../Platform/Config/SyntaxCompatible.h"


#define PI 3.141592654f
#define EPSILON 0.0001f


namespace tgon
{


class TGON_API GenericMath
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


TGON_CONSTEXPR_OR_INLINE float GenericMath::DegreeToRadian(
	float angle ) 
{
	return angle*( PI/180.f );
}

TGON_CONSTEXPR_OR_INLINE float GenericMath::RadianToDegree(
		float radian ) 
{
	return radian*( 180.f/PI );
}

TGON_CONSTEXPR float GenericMath::Lerp(
	float from,
	float to,
	float t ) 
{
	return from + (( to-from )*t );
}

inline float tgon::GenericMath::Smoothstep(
	float from,
	float to,
	float t ) 
{
	const float _t = 
		GenericMath::Clamp(( t-from )/( to-from ),
								   0.0f,
								   1.0f );
	return _t*_t*( 3-2*_t );
}

inline TVector3 GenericMath::Hermite(
	const TVector3& a,
	const TVector3& b,
	const TVector3& c,
	float t )
{
	return {(( 1-t )*( 1-t )*a ) +
			( 2*t*( 1-t )*b ) +
			( t*t*c )};
}

TGON_CONSTEXPR_OR_INLINE float GenericMath::Max(
	float first,
	float second )
{
	return ( first >= second ) ? first : second;
}

TGON_CONSTEXPR_OR_INLINE float GenericMath::Min(
	float first, 
	float second )
{
	return ( first <= second ) ? first : second;
}

TGON_CONSTEXPR_OR_INLINE float GenericMath::Abs(
	float value )
{
	return ( value < 0 ) ? -value : value;
}

TGON_CONSTEXPR_OR_INLINE float tgon::GenericMath::Clamp(
	float value, float min, float max ) 
{
	return GenericMath::Max(
		GenericMath::Min( value, max ),
		min
	);
}

BOOST_FORCEINLINE float tgon::GenericMath::Sqrt(
	float value )
{
	return std::sqrt( value );
}

BOOST_FORCEINLINE uint32_t GenericMath::GenerateHash(
	const char* str )
{
	return x65599Hash( str, std::strlen( str ));
}


}