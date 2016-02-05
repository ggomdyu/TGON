#include "stdafx.h"
#include "IObject.h"


tgon::IObject::IObject( )
{
}


tgon::IObject::~IObject( )
{
}



void tgon::IObject::FrameMove( float elapsedTime )
{
	for ( const auto& iter : m_mapComponents ) {
		iter.second->FrameMove( elapsedTime );
	}
}
