#include "PrecompiledHeader.h"
#include "TEventType.h"



tgon::TEventType::TEventType( const char * eventName ) :
	m_eventNameHash( TMath::GenerateHash( eventName ))
{
}
