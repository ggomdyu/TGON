/*
* Author : Junho-Cha
* Date : 04/02/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <xmmintrin.h>
#include "../../Config/Compiler/SyntaxCompatible.hpp"


namespace tgon
{


using TReg128 = __m128;
using TReg128Int = __m128i;


TGON_FORCEINLINE TReg128 MakeReg128( )
{
	return _mm_setzero_ps( );
}

TGON_FORCEINLINE TReg128 MakeReg128( float x, float y, float z )
{
	return _mm_setr_ps( x, y, z, 0.f );
}

TGON_FORCEINLINE TReg128 MakeReg128( float x, float y, float z, float w )
{
	return _mm_setr_ps( x, y, z, w );
}


/*
	Arithmetic operators
*/

TGON_FORCEINLINE TReg128 operator+( 
	const TReg128& v1,
	const TReg128& v2 )
{
	return _mm_add_ps( v1, v2 );
}

TGON_FORCEINLINE TReg128 operator-(
	const TReg128& v1,
	const TReg128& v2 )
{
	return _mm_sub_ps( v1, v2 );
}

TGON_FORCEINLINE TReg128 operator*( 
	const TReg128& v1,
	const TReg128& v2 )
{
	return _mm_mul_ps( v1, v2 );
}

TGON_FORCEINLINE TReg128 operator/( 
	const TReg128& v1, 
	const TReg128& v2 )
{
	return _mm_div_ps( v1, v2 );
}

TGON_FORCEINLINE TReg128 operator+( 
	const TReg128& v, 
	float scalar )
{	
	return _mm_add_ps( v, _mm_set1_ps( scalar ));
}

TGON_FORCEINLINE TReg128 operator-( 
	const TReg128& v, 
	float scalar )
{
	return _mm_sub_ps( v, _mm_set1_ps( scalar ));
}

TGON_FORCEINLINE TReg128 operator*( 
	const TReg128& v, 
	float scalar )
{
	return _mm_mul_ps( v, _mm_set1_ps( scalar ));
}

TGON_FORCEINLINE TReg128 operator/(
	const TReg128& v,
	float scalar )
{
	return _mm_div_ps( v, _mm_set1_ps( scalar ));
}


/*
	Comparison operators
*/

TGON_FORCEINLINE TReg128 operator!=( 
	const TReg128& v1, 
	const TReg128& v2 )
{
	return _mm_cmpneq_ps( v1, v2 );
}

TGON_FORCEINLINE TReg128 operator==( 
	const TReg128& v1, 
	const TReg128& v2 )
{
	return _mm_cmpeq_ps( v1, v2 );
}


}