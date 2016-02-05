#include "stdafx.h"
#include "RTTIUtil.h"

bool DynamicCast( const RTTI* from, const RTTI* to )
{
	const RTTI* head = from;

	while ( head != nullptr )
	{
		if ( head == to )
		{
			return true;
		}
		head = head->GetParentRTTI( );
	}

	return false;
}