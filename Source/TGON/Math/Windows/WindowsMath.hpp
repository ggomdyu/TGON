#pragma once
#include "WindowsMath.h"


float tgon::WindowsMath::Round( float val ) 
{
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