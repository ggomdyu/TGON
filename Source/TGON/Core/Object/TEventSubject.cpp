#include "PrecompiledHeader.h"
#include "TEventSubject.h"


decltype( tgon::TEventSubject::ms_globalMap ) tgon::TEventSubject::ms_globalMap;


tgon::TEventSubject::~TEventSubject( )
{
	this->UnsubscribeAllEvents( );
}

void tgon::TEventSubject::UnsubscribeEvent( TEvent eventType )
{
	auto eventMapIter = ms_globalMap.find( eventType );
	
	// Does eventMapIter exist?
	if ( eventMapIter != ms_globalMap.end( ))
	{
		// Then, delete all of event handlers
		for ( auto eventHandler : eventMapIter->second )
		{
			delete eventHandler.second;
			eventHandler.second = nullptr;
		}

	 	eventMapIter->second.erase( this );
	}
}

void tgon::TEventSubject::UnsubscribeAllEvents( )
{
	// Unsubscribe global event
	for ( auto eventMapIter : ms_globalMap )
	{
		auto eveneHandlerIter = eventMapIter.second.find( this );

		// Does exist event handlers?
		if ( eveneHandlerIter != eventMapIter.second.end( ))
		{
			delete eveneHandlerIter->second;
			eveneHandlerIter->second = nullptr;
		}

		eventMapIter.second.erase( this );
	}
}

void tgon::TEventSubject::NotifyEvent( TEvent eventType )
{
	for ( auto eventMap : ms_globalMap )
	{
		// Find event type which we want to notify 
		if ( eventMap.first != eventType )
		{
			continue;
		}

		for ( auto listener : eventMap.second )
		{
			listener.second->Notify( );
		}
	}
}
