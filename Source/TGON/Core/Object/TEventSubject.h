/*
* Author : Cha Junho
* Date : 07/10/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "TEventListener.h"
#include "TType.h"
#include <boost/variant.hpp>

/*
	BEAR IN MIND THIS CODE RAISE SERIOUS CODE BLOAT
	SO, DO NOT MAKE MANY EVENTS THROUGHT TGON_GENERATE_EVENT
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
namespace tgon {\
namespace details {\
	template<typename ReceiverTy>\
	class SubscribeEventImpl<eventName, ReceiverTy, __VA_ARGS__>\
	{\
	private:\
		template <typename ReceiverTy>\
		using HandlerFunction = void( ReceiverTy::* )( __VA_ARGS__ );\
	public:\
		static void SubscribeEvent( HandlerFunction<ReceiverTy> handlerFunc ) { /*Do not insert anything here*/ }\
	};\
	template <typename CallerTy>\
	class NotifyEventImpl<eventName, CallerTy, __VA_ARGS__>\
	{\
	public:\
		static void NotifyEvent( __VA_ARGS__ ) { /*Do not insert anything here*/ }\
	};\
}\
}


namespace tgon
{


namespace details
{
	// Check Event Handler function has correct arguments type and number
	template<typename EventTy, typename ReceiverTy, typename... HandlerFuncArgs>
	class SubscribeEventImpl
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
	class NotifyEventImpl
	{
	public:
		static void NotifyEvent( HandlerFuncArgs... args )
		{
			static_assert( false, "Failed to notify event. Check paramter type and number passed correctly." );
		}
	};
}


class TGON_API TEventSubject :
	public TObject
{
/*
	Type definitions
*/
	class Dummy {};

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
	// @note Subscribe specific event's handling. 
	// @param eventType Specify what you want to subscribe
	// @param handlerFunction Set Event handler function. It will be invoken when event handled
	//
	template<typename EventTy, typename ReceiverTy, typename... HandlerFuncArgs>
	void SubscribeEvent( HandlerFunction<ReceiverTy, HandlerFuncArgs...> handlerFunc ); // = delete;

	//
	// @note Unsubscribe specific event that this object subscribed
	// @param eventType Specify what you want to unsubscribe
	//
	template<typename EventTy>
	void UnsubscribeEvent( );


	//
	// @note Unsubscribe all of events this object subscribed
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
	template <typename EventTy, typename... HandlerFuncArgs>
	void NotifyEvent( HandlerFuncArgs... args );

private:
	void UnsubscribeEventImpl( uint32_t eventTypeHashCode );

	TEventListener** GetEventSubscriptionInfo( uint32_t eventHash );


/*
	Private variables
*/
private:
	static EventListenerRepo ms_globalEventListenerRepo;
};


template<typename EventTy, typename ReceiverTy, typename... HandlerFuncArgs>
inline void TEventSubject::SubscribeEvent( HandlerFunction<ReceiverTy, HandlerFuncArgs...> handlerFunc ) // = delete;
{
	// If event handler is not generated, then this code will output compile error.
	// This code will be deleted in release mode.
	details::SubscribeEventImpl<EventTy, ReceiverTy, HandlerFuncArgs...>::SubscribeEvent( handlerFunc );

	// And register listener info to table.
	TEventListener** ppListener = GetEventSubscriptionInfo( EventTy::GetType( ).GetHashCode( ));

	*ppListener = new TEventListenerImpl<ReceiverTy, HandlerFuncArgs...>( 
		this, handlerFunc );
}

template<typename EventTy>
inline void TEventSubject::UnsubscribeEvent( )
{
	UnsubscribeEventImpl( EventTy::GetType( ).GetHashCode( ));
}

template<typename EventTy, typename ...HandlerFuncArgs>
inline void TEventSubject::NotifyEvent( HandlerFuncArgs... args )
{
	// If parameter is not passed correctly, this code will output compile error.
	// This code will be deleted in release mode.
	details::NotifyEventImpl<EventTy, Dummy, HandlerFuncArgs...>::NotifyEvent( args... );

	// Does exist subscriber?
	auto iter = ms_globalEventListenerRepo.find( EventTy::GetType( ).GetHashCode( ));
	if ( iter != ms_globalEventListenerRepo.end( ))
	{
		// Then, iterate the repository and notify event to them
		for ( auto& listener : iter->second )
		{
			static_cast<TEventListenerImpl<Dummy, HandlerFuncArgs...>*>(
				listener.second )->Notify( args... );
		}
	}
}

}
