/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description :
*/


#pragma once
#include <xmmintrin.h>
#include "../Generic/GenericPlatformMath.h"


namespace tgon
{


class WindowsPlatformMath;
typedef WindowsPlatformMath MathImpl;

class TGON_API WindowsPlatformMath : public GenericPlatformMath
{
public:
	static float Round( float val );
	static int32_t RoundToInt( float val );

	static float Floor( float val );
	static int32_t FloorToInt( float val );

private:
	WindowsPlatformMath( ) = delete;
	~WindowsPlatformMath( ) = delete;
};


inline float tgon::WindowsPlatformMath::Round( 
	float val ) 
{
	return static_cast<float>( RoundToInt( val ));
}

inline int32_t tgon::WindowsPlatformMath::RoundToInt( 
	float val ) 
{
	return _mm_cvt_ss2si( _mm_set_ss(
		val+val+0.5f )) >> 1;
}

inline float tgon::WindowsPlatformMath::Floor( 
	float val ) 
{
	return static_cast<float>(
		FloorToInt( val ));
}

inline int32_t tgon::WindowsPlatformMath::FloorToInt(
	float val ) 
{
	return ( _mm_cvt_ss2si( _mm_set_ss(
		val+val-0.5f )) >> 1 );
}


}