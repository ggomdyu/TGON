/*
* 작성자 : 차준호
* 작성일 : 2016-03-14
* 최종 수정 :
* 최종 수정일 :
* Description :
*/


#pragma once
#include <stdint.h>
#include "../../Config/Compiler/SyntaxCompatible.hpp"


namespace tgon
{


class LayeredMath
{
private:
	LayeredMath( ) = delete;
	~LayeredMath( ) = delete;

public:
	TGON_STATIC_CONSTEXPR_VALUE( float, EPSILON, 0.0001f )
	TGON_STATIC_CONSTEXPR_VALUE( float, PI, 3.141592654f )

	static TGON_CONSTEXPR float DegreeToRadian( float angle );
	static TGON_CONSTEXPR float RadianToDegree( float radian );

	static float Sqrt( float value );

	template<class T>
	static TGON_CONSTEXPR T Max( const T first,
								 const T second );
	template<class T>
	static TGON_CONSTEXPR T Min( const T first,
								 const T second );
	template<class T>
	static TGON_CONSTEXPR T Abs( const T value );
	
	template<class T>
	static TGON_CONSTEXPR T Clamp( const T value,
								   const T min,
								   const T max );

	/*
		Random number generator
	*/
	static float FRand( ) ; // 0.0 ~ 1.0
	static float FRand( const float min,
						const float max );

	/*
		Hashing
	*/
	static uint32_t GenerateHash( const char* str );


	/*
		Interpolation
	*/
	static TGON_CONSTEXPR float Lerp( const float from,
									  const float to,
									  const float t );

	static float Smoothstep( const float from,
							 const float to,
							 const float t );


private:
	//	WELL Random number( 0.0~1.0 ) generator
	//	Faster than Mersenne-Twister 40% or so 
	//	cf. http://www.iro.umontreal.ca/~panneton/WELLRNG.html
	static float WELLRNG512a( );

	// Hashing
	static uint32_t x65599Hash( const char* str, size_t length );
	static uint32_t SDBMHash( const char* str, size_t length );
};


}


#include "LayeredMath.hpp"