#include "stdafx.h"
#include "IObject.h"


tgon::IObject::IObject( )
{
}


tgon::IObject::~IObject( )
{
}



void tgon::IObject::Run( float elapsedTime )
{
	for ( const auto& iter : m_components ) {
		iter.second->Run( elapsedTime );
	}
}
