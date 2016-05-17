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


namespace tgon
{
class TGON_API GenericPlatformMath
{
public:
	static const float EPSILON;
	static const float PI;

	static float DegreeToRadian( float degree );
	static double DegreeToRadian( double degree );
	static float RadianToDegree( float radian );
	static double RadianToDegree( double radian );

	template<class _Ty> static _Ty Sqrt( _Ty value );
	template<class _Ty> static _Ty Max( _Ty first, _Ty second );
	template<class _Ty> static _Ty Min( _Ty first, _Ty second );
	template<class _Ty> static _Ty Abs( _Ty value );
	template<class _Ty> static _Ty Clamp( _Ty value, _Ty min, _Ty max );

	/*
		Hashing
	*/
	static uint32_t GenerateHash( const char* str );

	/*
		Interpolation
	*/
	static float Lerp( float from, float to, float t );
	static float Smoothstep( float from, float to, float t );
	static TVector3 Hermite( const TVector3& a, const TVector3& b, const TVector3& c, float t );

private:
	
	// x65599 Hasher
	static uint32_t x65599Hash( const char* str, size_t length );
};


BOOST_FORCEINLINE float GenericPlatformMath::DegreeToRadian(
	float angle ) 
{
	return angle*( PI/180.f );
}

BOOST_FORCEINLINE double GenericPlatformMath::DegreeToRadian(
	double degree )
{
	return degree*( PI/180.0 );
}

BOOST_FORCEINLINE float GenericPlatformMath::RadianToDegree(
		float radian ) 
{
	return radian*( 180.f/PI );
}

BOOST_FORCEINLINE double GenericPlatformMath::RadianToDegree(
	double radian )
{
	return radian*( 180.0/PI );
}

BOOST_FORCEINLINE float GenericPlatformMath::Lerp(
	float from,
	float to,
	float t ) 
{
	return from + (( to-from )*t );
}

BOOST_FORCEINLINE float tgon::GenericPlatformMath::Smoothstep(
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

BOOST_FORCEINLINE TVector3 GenericPlatformMath::Hermite(
	const TVector3& a,
	const TVector3& b,
	const TVector3& c,
	float t )
{
	return {( std::pow(( 1-t ), 2 )*a ) +
			( 2*t*( 1-t )*b ) +
			( t*t*c )};
}

template<class _Ty>
BOOST_FORCEINLINE _Ty GenericPlatformMath::Max(
	_Ty first, 
	_Ty second )
{
	return ( first >= second ) ? first : second;
}

template<class _Ty>
BOOST_FORCEINLINE _Ty GenericPlatformMath::Min(
	_Ty first, 
	_Ty second )
{
	return ( first <= second ) ? first : second;
}

template<class _Ty>
BOOST_FORCEINLINE _Ty GenericPlatformMath::Abs(
	_Ty value )
{
	return std::abs( value );
}

template<class _Ty>
BOOST_FORCEINLINE _Ty tgon::GenericPlatformMath::Clamp(
	_Ty value, _Ty min, _Ty max ) 
{
	return GenericPlatformMath::Max(
		GenericPlatformMath::Min( value, max ),
		min
	);
}

template<class _Ty>
BOOST_FORCEINLINE _Ty tgon::GenericPlatformMath::Sqrt(
	_Ty value )
{
	return std::sqrt( value );
}

BOOST_FORCEINLINE uint32_t GenericPlatformMath::GenerateHash(
	const char* str )
{
	return x65599Hash( str, std::strlen( str ));
}


}