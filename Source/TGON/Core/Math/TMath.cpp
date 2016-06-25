#include "PrecompiledHeader.h"
#include "TMath.h"


float tgon::TMath::PI = 3.141592654f;
float tgon::TMath::EPSILON = 0.0001f;

uint32_t tgon::TMath::x65599Hash( const char* str, size_t length ) 
{
	uint32_t hash = 0;
	for ( uint32_t i = 0; i < length; ++i )
	{
		hash = 65599*hash + str[i];
	}

	return hash^( hash >> 16 );
}