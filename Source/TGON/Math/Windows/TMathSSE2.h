/*
* 작성자 : 차준호
* 작성일 : 2016-04-02
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <xmmintrin.h>

namespace tgon
{


using TReg128 = __m128;
using TReg128Int = __m128i;


inline TReg128 MakeReg128( )
{
	return _mm_setzero_ps( );
}

inline TReg128 MakeReg128( float x, float y, float z )
{
	return _mm_setr_ps( x, y, z, 0.f );
}

inline TReg128 MakeReg128( float x, float y, float z, float w )
{
	return _mm_setr_ps( x, y, z, w );
}


/*
	Arithmetic operators
*/
inline TReg128 operator+( const TReg128& v1, const TReg128& v2 )
{
	return _mm_add_ps( v1, v2 );
}

inline TReg128 operator-( const TReg128& v1, const TReg128& v2 )
{
	return _mm_sub_ps( v1, v2 );
}

inline TReg128 operator*( const TReg128& v1, const TReg128& v2 )
{
	return _mm_mul_ps( v1, v2 );
}

inline TReg128 operator/( const TReg128& v1, const TReg128& v2 )
{
	return _mm_div_ps( v1, v2 );
}

inline TReg128 operator+( const TReg128& v, float scalar )
{	
	return _mm_add_ps( v, _mm_set1_ps( scalar ));
}

inline TReg128 operator-( const TReg128& v, float scalar )
{
	return _mm_sub_ps( v, _mm_set1_ps( scalar ));
}

inline TReg128 operator*( const TReg128& v, float scalar )
{
	return _mm_mul_ps( v, _mm_set1_ps( scalar ));
}

inline TReg128 operator/( const TReg128& v, float scalar )
{
	return _mm_div_ps( v, _mm_set1_ps( scalar ));
}


/*
	Comparison operators
*/
inline TReg128 operator!=( const TReg128& v1, const TReg128& v2 )
{
	return _mm_cmpneq_ps( v1, v2 );
}

inline TReg128 operator==( const TReg128& v1, const TReg128& v2 )
{
	return _mm_cmpeq_ps( v1, v2 );
}


}