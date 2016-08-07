#include "PrecompiledHeader.h"
#include "TEventSubject.h"


decltype( tgon::TEventSubject::ms_globalEventListenerRepo ) tgon::TEventSubject::ms_globalEventListenerRepo;


tgon::TEventSubject::~TEventSubject( )
{
	this->UnsubscribeAllEvents( );
}

void tgon::TEventSubject::UnsubscribeEvent( TEventType eventType )
{
	auto iter = ms_globalEventListenerRepo.find( eventType.GetHashCode( ));
	
	// Does eventMapIter exist?
	if ( iter != ms_globalEventListenerRepo.end( ))
	{
		// Then, delete all of event handlers
		for ( auto eventHandler : iter->second )
		{
			delete eventHandler.second;
			eventHandler.second = nullptr;
		}

	 	iter->second.erase( this );
	}
}

void tgon::TEventSubject::UnsubscribeAllEvents( )
{
	// Unsubscribe global event
	for ( auto& eventMapIter : ms_globalEventListenerRepo )
	{
		auto eventHandlerIter = eventMapIter.second.find( this );

		// Does exist event handlers?
		if ( eventHandlerIter != eventMapIter.second.end( ))
		{
			delete eventHandlerIter->second;
			eventHandlerIter->second = nullptr;
		}

		eventMapIter.second.erase( this );
	}
}

void tgon::TEventSubject::NotifyEvent( TEventType eventType )
{
	for ( auto eventMap : ms_globalEventListenerRepo )
	{
		// Find event type which we want to notify 
		if ( eventMap.first != eventType.GetHashCode( ))
		{
			continue;
		}

		for ( auto listener : eventMap.second )
		{
			listener.second->Notify( );
		}
	}
}
