/*
* Author : Cha Junho
* Date : 07/10/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "TEventListener.h"
#include "TType.h"


#define TGON_GENERATE_EVENT( eventName )\
namespace tgon\
{\
	namespace TEvent\
	{\
		tgon::TEventType eventName( #eventName );\
	}\
}

namespace tgon
{


using TEventType = TType;

class TGON_API TEventSubject :
	public TObject
{
/*
	Type definitions
*/
	template <typename ReceiverTy, typename... HandlerFuncArgs>
	using HandlerFunction = void( ReceiverTy::* )( HandlerFuncArgs... );

	//
	using ListenerRepo = std::unordered_map<TEventSubject*, TEventListener*>;
	
	// uint32_t is TEventType's hash code.
	// ListenerRepo is the subscriber list of this event.
	using EventListenerRepo = std::unordered_map<uint32_t, ListenerRepo>;

	
/*
	Generator
*/
public:
	TGON_GENERATE_OBJECT_INTERFACE( TEventSubject, TObject )


public:
	/*
		Commands
	*/
	//
	// Subscribe specific event's handling. 
	//
	// @param eventType Specify what you want to subscribe
	// @param handlerFunction Set Event handler function. It will be invoken when event handled
	//
	template<typename EventTy, typename ReceiverTy, typename... HandlerFuncArgs>
	void SubscribeEvent( HandlerFunction<ReceiverTy, HandlerFuncArgs...> handlerFunc )
	{
		ms_globalEventListenerRepo[EventTy::GetType( ).GetHashCode( )][this] = new TEventListenerImpl<ReceiverTy, HandlerFuncArgs...>(
			this, handlerFunc );
	}

	//
	// Unsubscribe specific event that this object subscribed
	//
	// @param eventType Specify what you want to unsubscribe event
	//
	void UnsubscribeEvent( TEventType eventType );

	//
	// Unsubscribe all of events this object subscribed
	//
	void UnsubscribeAllEvents( );


/*
	Cons/Destructor
*/
public:
	TEventSubject( ) = default;

	virtual ~TEventSubject( );


/*
	Protect functions
*/
protected:
	template <typename EventTy, typename CallerTy, typename... EventHandlerArgs>
	void NotifyEvent( EventHandlerArgs... args )
	{
		auto listenerRepoIter = ms_globalEventListenerRepo.find( EventTy::GetType( ).GetHashCode( ));

		// Does exist event subscriber?
		if ( listenerRepoIter != ms_globalEventListenerRepo.end( ))
		{
			for ( auto& listener : listenerRepoIter->second )
			{
				static_cast<TEventListenerImpl<CallerTy, EventHandlerArgs...>*>( 
					listener.second )->Notify( args... );
			}
		}
	}


/*
	Private variables
*/
private:
	static EventListenerRepo ms_globalEventListenerRepo;
};


}