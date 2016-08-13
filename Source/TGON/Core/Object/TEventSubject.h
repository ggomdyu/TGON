/*
* Author : Cha Junho
* Date : 07/10/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "TEventListener.h"
#include "TType.h"


/*
	BEAR IN MIND THIS CODE RAISE SERIOUS CODE BLOAT
	SO, DO NOT MAKE MANY EVENT THROUGHT TGON_GENERATE_EVENT
*/


//
// Generate event type.
//
// @param eventName (Ex): E_DESTROY, E_UPDATE, etc
// @param ... The parameters what event will aceept in event handler
//
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
template <typename CallerTy>\
class NotifyEventProxy<eventName, CallerTy, __VA_ARGS__>\
{\
public:\
	static void NotifyEvent( __VA_ARGS__ ) {}\
};\
}


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

template <typename EventTy, typename CallerTy, typename... HandlerFuncArgs>
class NotifyEventProxy
{
public:
	static void NotifyEvent( HandlerFuncArgs... args )
	{
		static_assert( false, "Failed to notify event. Check paramter type and number passed correctly." );
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
	void SubscribeEvent( HandlerFunction<ReceiverTy, HandlerFuncArgs...> handlerFunc ); // = delete;

	//
	// Unsubscribe specific event that this object subscribed
	//
	// @param eventType Specify what you want to unsubscribe event
	//
	template<typename EventTy>
	void UnsubscribeEvent( );

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
	template <typename EventTy, typename CallerTy, typename... HandlerFuncArgs>
	void NotifyEvent( HandlerFuncArgs... args ); // = delete;


private:
	void UnsubscribeEventImpl( uint32_t eventTypeHashCode );


/*
	Private variables
*/
private:
	static EventListenerRepo ms_globalEventListenerRepo;
};


template<typename EventTy, typename ReceiverTy, typename... HandlerFuncArgs>
inline void TEventSubject::SubscribeEvent( HandlerFunction<ReceiverTy, HandlerFuncArgs...> handlerFunc ) // = delete;
{
	static_assert( std::is_convertible<EventTy, tgon::TObject>::value,
		"The template paramter only accept class based on tgon::TObject." );

	// If event handler is not generated, then this code will output compile error.
	SubscribeEventProxy<EventTy, ReceiverTy, HandlerFuncArgs...>::SubscribeEvent( handlerFunc );

	// And register listener info to table.
	ms_globalEventListenerRepo[EventTy::GetType( ).GetHashCode( )][this] = 
		new TEventListenerImpl<ReceiverTy, HandlerFuncArgs...>( this, handlerFunc );
}

template<typename EventTy>
inline void TEventSubject::UnsubscribeEvent( )
{
	UnsubscribeEventImpl( EventTy::GetType( ).GetHashCode( ));
}

template<typename EventTy, typename CallerTy, typename ...HandlerFuncArgs>
inline void TEventSubject::NotifyEvent( HandlerFuncArgs ...args )
{
	// If parameter is not passed correctly, this code will output compile error.
	NotifyEventProxy<EventTy, CallerTy, HandlerFuncArgs...>::NotifyEvent( args... );

	// Does exist event subscriber?
	auto listenerRepoIter = ms_globalEventListenerRepo.find( EventTy::GetType( ).GetHashCode( ));
	if ( listenerRepoIter != ms_globalEventListenerRepo.end( ))
	{
		// Then, iterate the repository and notify event to them
		for ( auto& listener : listenerRepoIter->second )
		{
			static_cast<TEventListenerImpl<CallerTy, HandlerFuncArgs...>*>(
				listener.second )->Notify( args... );
		}
	}
}

}
