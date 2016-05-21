/*
* Author : Junho-Cha
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description :
*/


#pragma once
#include <xmmintrin.h>
#include "../Generic/GenericMath.h"


namespace tgon
{


using MathImpl = class WindowsMath;

class TGON_API WindowsMath : public GenericMath
{
public:
	static float Round( float val );
	static int32_t RoundToInt( float val );

	static float Floor( float val );
	static int32_t FloorToInt( float val );

private:
	WindowsMath( ) = delete;
	~WindowsMath( ) = delete;
};


inline float tgon::WindowsMath::Round( 
	float val ) 
{
	return static_cast<float>( RoundToInt( val ));
}

inline int32_t tgon::WindowsMath::RoundToInt( 
	float val ) 
{
	return _mm_cvt_ss2si( _mm_set_ss( val+val+0.5f )) >> 1;
}

inline float tgon::WindowsMath::Floor( 
	float val ) 
{
	return static_cast<float>( FloorToInt( val ));
}

inline int32_t tgon::WindowsMath::FloorToInt(
	float val ) 
{
	return ( _mm_cvt_ss2si( _mm_set_ss( val+val-0.5f )) >> 1 );
}


}