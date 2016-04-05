/*
* 작성자 : 차준호
* 작성일 : 2016-03-14
* 최종 수정 :
* 최종 수정일 :
* Description :
*/


#pragma once
#include <xmmintrin.h>

#include "../../Config/Platform/PlatformProperty.h"
#include "../../Config/Compiler/SyntaxCompatible.hpp"
#include "../Layered/LayeredMath.h"

namespace tgon
{


class WindowsMath;
typedef WindowsMath MathImpl;

class WindowsMath : public LayeredMath
{
private:
	WindowsMath( ) = delete;
	~WindowsMath( ) = delete;

public:
	/*
		SSE2 Intrinsics
	*/

#ifdef TGON_SUPPORT_SSE2
	inline static float Round( float val );
	inline static int32_t RoundToInt( float val );

	inline static float Floor( float val );
	inline static int32_t FloorToInt( float val );
#endif
};


}

float tgon::WindowsMath::Round( float val ) 
{
	/*
		TODO: REPAIR code
	*/
	return static_cast<float>( RoundToInt( val ));
}

int32_t tgon::WindowsMath::RoundToInt( float val ) 
{
	return _mm_cvt_ss2si( _mm_set_ss( val + val + 0.5f )) >> 1;
}


float tgon::WindowsMath::Floor( float val ) 
{
	return static_cast<float>( FloorToInt( val ));
}

int32_t tgon::WindowsMath::FloorToInt( float val ) 
{
	return ( _mm_cvt_ss2si( _mm_set_ss( val+val-0.5f )) >> 1 );
}