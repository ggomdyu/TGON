#include "PrecompiledHeader.h"
#include "Mathf.h"


namespace tgon
{


uint32_t Math::x65599Hash( const char* str, std::size_t length )
{
	uint32_t hash = 0;
	for ( uint32_t i = 0; i < length; ++i )
	{
		hash = 65599*hash + str[i];
	}

	return hash^( hash >> 16 );
}


} /*namespace tgon*/