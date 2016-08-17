#include "PrecompiledHeader.h"
#include "TEventSubject.h"


decltype( tgon::TEventSubject::ms_globalEventListenerRepo ) tgon::TEventSubject::ms_globalEventListenerRepo;


tgon::TEventSubject::~TEventSubject( )
{
	this->UnsubscribeAllEvents( );
}

void tgon::TEventSubject::UnsubscribeEventImpl( uint32_t eventTypeHashCode )
{
	auto iter = ms_globalEventListenerRepo.find( eventTypeHashCode );
	
	// Does exist subscribers?
	if ( iter != ms_globalEventListenerRepo.end( ))
	{
		auto& eventSubscribers = iter->second;

		// Then, delete all of listener
		for ( auto& eventListener : eventSubscribers )
		{
			delete eventListener.second;
			eventListener.second = nullptr;
		}

		eventSubscribers.erase( this );
	}
}

void tgon::TEventSubject::UnsubscribeAllEvents( )
{
	// Unsubscribe global event
	for ( auto eventMapIter : ms_globalEventListenerRepo )
	{
		auto eventListenerIter = eventMapIter.second.find( this );

		// Does exist event handlers?
		if ( eventListenerIter != eventMapIter.second.end( ))
		{
			delete eventListenerIter->second;
			eventListenerIter->second = nullptr;
		}

		eventMapIter.second.erase( this );
	}
}


tgon::TEventListener** tgon::TEventSubject::GetEventSubscriptionInfo( uint32_t eventHashCode )
{
	TEventListener** ppListener = &ms_globalEventListenerRepo[eventHashCode][this];
	if ( *ppListener )
	{
		assert( false && "You already had subscribed this event!" );
	}

	return ppListener;
}