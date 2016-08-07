#include "PrecompiledHeader.h"
#include "TEventListener.h"


tgon::TEventListener::TEventListener( TEventSubject* receiver ) :
	m_receiver( receiver )
{
	assert( receiver );
}