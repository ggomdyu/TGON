#include "PrecompiledHeader.h"
#include "EventObserver.h"


namespace tgon
{


EventObserver::EventObserver( EventObject* receiver ) :
	m_receiver( receiver )
{
	assert( receiver );
}

EventObserver::~EventObserver( )
{
}


} /*namespace tgon*/
