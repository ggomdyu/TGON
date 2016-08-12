/*
* Author : Cha Junho
* Date : 07/10/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "TEventListener.h"
#include "TType.h"


namespace tgon
{


using TEventType = TType;


// Check Event Handler function has correct arguments type and number
template<typename EventTy, typename ReceiverTy, typename... HandlerFuncArgs>
class SubscribeEventProxy
{
private:
	template <typename ReceiverTy, typename... HandlerFuncArgs>
	using HandlerFunction = void( ReceiverTy::* )( HandlerFuncArgs... );

public:
	static void SubscribeEvent( HandlerFunction<ReceiverTy, HandlerFuncArgs...> handlerFunc )
	{
		static_assert( false, "Failed to subscribe event. Check event handler's paramter type and number exactly correct." );
	}
};


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


/*
	Commands
*/
public:
	//
	// Subscribe specific event's handling. 
	//
	// @param eventType Specify what you want to subscribe
	// @param handlerFunction Set Event handler function. It will be invoken when event handled
	//
	template<typename EventTy, typename ReceiverTy, typename... HandlerFuncArgs>
	void SubscribeEvent( HandlerFunction<ReceiverTy, HandlerFuncArgs...> handlerFunc ) // = delete;
	{
		//static_assert( std::is_convertible<EventTy, TEventType>::value,
		//	"The template paramter only accept class based on TEventType." );

		// If event handler not generated, then this code will output compile error.
		SubscribeEventProxy<EventTy, ReceiverTy, HandlerFuncArgs...>::SubscribeEvent( handlerFunc );

		// And register listener info to table.
		ms_globalEventListenerRepo[EventTy::GetType( ).GetHashCode( )][this] = 
			new TEventListenerImpl<ReceiverTy, HandlerFuncArgs...>( this, handlerFunc );
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
		//static_assert( false, "You can't use unspecialized template of NotifyEvent. You can specialize easily by TGON_GENERATE_EVENT macro." );

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


#define TGON_GENERATE_EVENT( eventName, ... )\
struct eventName : public tgon::TObject\
{\
public:\
	TGON_GENERATE_OBJECT_INTERFACE( eventName, tgon::TObject )\
public:\
	virtual ~eventName( ) = default;\
};\
\
namespace tgon\
{\
\
template<typename ReceiverTy>\
class SubscribeEventProxy<eventName, ReceiverTy, __VA_ARGS__>\
{\
private:\
	template <typename ReceiverTy>\
	using HandlerFunction = void( ReceiverTy::* )( __VA_ARGS__ );\
	\
public:\
	static void SubscribeEvent( HandlerFunction<ReceiverTy> handlerFunc ) { /*Do not insert anything here*/ }\
};\
\
}
