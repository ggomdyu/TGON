/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description :
*/


#pragma once
#include <stdint.h>
#include "../TVector3.h"
#include "../../Config/SyntaxCompatible.h"
#include "../../Config/Build.h"


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

	template<class _Ty>
	static _Ty Sqrt( _Ty value );

	template<class _Ty>
	static _Ty Max( _Ty first, _Ty second );
	
	template<class _Ty>
	static _Ty Min( _Ty first, _Ty second );
	
	template<class _Ty>
	static _Ty Abs( _Ty value );
	
	template<class _Ty>
	static _Ty Clamp( _Ty value, _Ty min, _Ty max );


	/*
		Random number generator
	*/
	static float FRand( ) ; // 0.0 ~ 1.0
	static float FRand( float min, float max );


	/*
		Hashing
	*/
	static uint32_t GenerateHash( const char* str );


	/*
		Interpolation
	*/
	static float Lerp(
		float from, float to, float t );

	static float Smoothstep(
		float from, float to, float t );

	static TVector3 Hermite(
		const TVector3& a,
		const TVector3& b, 
		const TVector3& c,
		float t );


private:
	GenericPlatformMath( ) = delete;
	~GenericPlatformMath( ) = delete;


	//	WELL Random number generator
	//	It's faster than the mers enne-Twister 40% or so 
	//	cf. http://www.iro.umontreal.ca/~panneton/WELLRNG.html
	static float WELLRNG512a( );
	
	// x65599 Hasher
	static uint32_t x65599Hash( const char* str, size_t length );
};


TGON_FORCEINLINE float GenericPlatformMath::DegreeToRadian(
	float angle ) 
{
	return angle*( PI/180.f );
}

TGON_FORCEINLINE double GenericPlatformMath::DegreeToRadian(
	double degree )
{
	return degree*( PI/180.0 );
}

TGON_FORCEINLINE float GenericPlatformMath::RadianToDegree(
		float radian ) 
{
	return radian*( 180.f/PI );
}

TGON_FORCEINLINE double GenericPlatformMath::RadianToDegree(
	double radian )
{
	return radian*( 180.0/PI );
}


TGON_FORCEINLINE float GenericPlatformMath::Lerp(
	float from,
	float to,
	float t ) 
{
	return from + (( to-from )*t );
}

TGON_FORCEINLINE float tgon::GenericPlatformMath::Smoothstep(
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

TGON_FORCEINLINE TVector3 GenericPlatformMath::Hermite(
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
TGON_FORCEINLINE _Ty GenericPlatformMath::Max(
	_Ty first, 
	_Ty second )
{
	return ( first >= second ) ? first : second;
}

template<class _Ty>
TGON_FORCEINLINE _Ty GenericPlatformMath::Min(
	_Ty first, 
	_Ty second )
{
	return ( first <= second ) ? first : second;
}

template<class _Ty>
TGON_FORCEINLINE _Ty GenericPlatformMath::Abs(
	_Ty value )
{
	return std::abs( value );
}

template<class _Ty>
TGON_FORCEINLINE _Ty tgon::GenericPlatformMath::Clamp(
	_Ty value, _Ty min, _Ty max ) 
{
	return GenericPlatformMath::Max(
		GenericPlatformMath::Min( value, max ),
		min
	);
}

template<class _Ty>
TGON_FORCEINLINE _Ty tgon::GenericPlatformMath::Sqrt(
	_Ty value )
{
	return std::sqrt( value );
}

TGON_FORCEINLINE float tgon::GenericPlatformMath::FRand( )
{
	return WELLRNG512a( );
}

TGON_FORCEINLINE float tgon::GenericPlatformMath::FRand(
	float min,
	float max ) 
{
	return min+( WELLRNG512a( )*( max-min ));
}

TGON_FORCEINLINE uint32_t GenericPlatformMath::GenerateHash(
	const char* str )
{
	return x65599Hash( str, std::strlen( str ));
}


}