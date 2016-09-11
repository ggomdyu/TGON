#include "PrecompiledHeader.h"
#include "EventObject.h"


namespace tgon
{


decltype( EventObject::ms_globalEventListenerRepo ) 
	EventObject::ms_globalEventListenerRepo;


EventObject::EventObject( )
{
}

EventObject::~EventObject( )
{
	this->UnsubscribeAllEvents( );
}

void EventObject::UnsubscribeEventImpl( uint32_t eventTypeHashCode )
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

void EventObject::SubscribeEventImpl( uint32_t eventHash, EventObserver* eventListener )
{
	EventObserver** ppListener = &ms_globalEventListenerRepo[eventHash][this];
	if ( *ppListener )
	{
		assert( false && "You already had subscribed this event!" );
	}
	else
	{
		*ppListener = eventListener;
	}
}

void EventObject::UnsubscribeAllEvents( )
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


} /*namespace tgon*/