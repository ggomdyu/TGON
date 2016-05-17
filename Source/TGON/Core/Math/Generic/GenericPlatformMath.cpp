#include "PrecompiledHeader.h"
#include "GenericPlatformMath.h"


const float tgon::GenericPlatformMath::EPSILON = 0.0001f;
const float tgon::GenericPlatformMath::PI = 3.141592654f;

uint32_t tgon::GenericPlatformMath::x65599Hash(
	const char* str,
	size_t length ) 
{
	uint32_t hash = 0;
	for ( uint32_t i = 0; i < length; ++i )
	{
		hash = 65599*hash + str[i];
	}

	return hash^( hash >> 16 );
}