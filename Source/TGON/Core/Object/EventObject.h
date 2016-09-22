/*
* Author : Cha Junho
* Date : 07/10/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "EventObserver.h"
#include "Type.h"

#include <cstdint>
#include <unordered_map>


/*
 * @note			Generate event type.
 * @param	eventName	e.g. E_DESTROY, E_UPDATE, etc
*/
#define TGON_GENERATE_EVENT( eventName, ... )\
struct eventName : public tgon::Object\
{\
public:\
	TGON_GENERATE_OBJECT_INTERFACE( eventName, tgon::Object )\
public:\
	virtual ~eventName( ) = default;\
};\
namespace tgon {\
namespace details {\
	template<typename ReceiverTy>\
	class SubscribeEventAssert<eventName, ReceiverTy, __VA_ARGS__>\
	{\
	private:\
		template <typename ReceiverTy>\
		using HandlerFunction = void( ReceiverTy::* )( __VA_ARGS__ );\
	public:\
		static void Assert( ) { /*Do not insert anything here*/ }\
	};\
	template <>\
	class NotifyEventAssert<eventName, __VA_ARGS__>\
	{\
	public:\
		static void Assert( ) { /*Do not insert anything here*/ }\
	};\
}\
} /*namespace tgon*/


namespace tgon
{ namespace details
{

/* Check Event Handler function has correct arguments type and number */
template<typename EventTy, typename ReceiverTy, typename... HandlerFuncArgs>
class SubscribeEventAssert
{
private:
	template <typename ReceiverTy, typename... HandlerFuncArgs>
	using HandlerFunction = void( ReceiverTy::* )( HandlerFuncArgs... );

public:
	static void Assert( )
	{
		static_assert( false, "Failed to subscribe event. Check event handler's paramter type and number exactly correct." );
	}
};

template <typename EventTy, typename... HandlerFuncArgs>
class NotifyEventAssert
{
public:
	static void Assert( )
	{
		static_assert( false, "Failed to notify event. Check paramter type and number passed correctly." );
	}
};
} /* namespace details */


class TGON_API EventObject :
	public Object
{
	// 
	// Type definitions
	// 
private:
	class Dummy {};
	using EventSubjectHash = uint32_t;
	
	template <typename ReceiverTy, typename... HandlerFuncArgs>
	using HandlerFunction = void( ReceiverTy::* )( HandlerFuncArgs... );

	/* @note This make fast to find observer list by owner pointer. */
	using EventObserverRepo = std::unordered_map<EventObject*, /*std::vector<*/EventObserver*>;
	/* @note Observer owner has observer list about event. */
	using EventObserverOwnerRepo = std::unordered_map<EventSubjectHash, EventObserverRepo>;

	// 
	// Generator
	// 
public:
	TGON_GENERATE_OBJECT_INTERFACE( EventObject, Object )

	// 
	// Commands
	// 
public:
	/*
	 * @note Subscribe specific event's handling. 
	 * @param eventType Specify what you want to subscribe
	 * @param handlerFunction Set Event handler function. It will be invoken when event handled
	*/
	template<typename EventTy, typename ReceiverTy, typename... HandlerFuncArgs>
	void SubscribeEvent( HandlerFunction<ReceiverTy, HandlerFuncArgs...> handlerFunc );

	/*
	 * @note Unsubscribe specific event that this object subscribed
	 * @param eventType Specify what you want to unsubscribe
	*/
	template<typename EventTy>
	void UnsubscribeEvent( );

	/* @note Unsubscribe all of events this object subscribed */
	void UnsubscribeAllEvents( );

	// 
	// Ctor/Dtor
	// 
public:
	EventObject( );
	virtual ~EventObject( );

	// 
	// Protected Commands
	// 
protected:
	/*
	 * @note Notify to all subscriber of specific event.
	 * @param eventArgs Event function arguments
	*/
	template <typename EventTy, typename... HandlerFuncArgs>
	void NotifyEvent( HandlerFuncArgs... eventArgs );

	// 
	// Internal works
	// 
private:
	void UnsubscribeEventImpl( uint32_t eventHash );
	void SubscribeEventImpl( uint32_t eventHash, EventObserver* eventListener );
	
	template<typename ReceiverTy, typename... HandlerFuncArgs>
	void NotifyEventImpl( uint32_t eventHash, HandlerFuncArgs... eventArgs );

	// 
	// Private variables
	// 
private:
	static EventObserverOwnerRepo ms_globalEventListenerRepo;
};


template<typename EventTy, typename ReceiverTy, typename... HandlerFuncArgs>
inline void EventObject::SubscribeEvent( HandlerFunction<ReceiverTy, HandlerFuncArgs...> handlerFunc )
{
	// If event handler is not generated, then this code will output compile error.
	// This code will be deleted in release mode.
	details::SubscribeEventAssert<EventTy, ReceiverTy, HandlerFuncArgs...>::Assert( );

	// And register listener info to table.
	this->SubscribeEventImpl( EventTy::GetType( ).GetHashCode( ), 
		new EventObserverImpl<ReceiverTy>( this, reinterpret_cast<HandlerFunction<ReceiverTy>>( handlerFunc ))
	);
}

template<typename EventTy>
inline void EventObject::UnsubscribeEvent( )
{
	UnsubscribeEventImpl( EventTy::GetType( ).GetHashCode( ));
}

template<typename EventTy, typename... HandlerFuncArgs>
inline void EventObject::NotifyEvent( HandlerFuncArgs... eventArgs )
{
	// If parameter is not passed correctly, this code will output compile error.
	// This code will be deleted in release mode.
	details::NotifyEventAssert<EventTy, HandlerFuncArgs...>::Assert( );

	this->NotifyEventImpl<Dummy, HandlerFuncArgs...>( EventTy::GetType( ).GetHashCode( ), eventArgs... );
}

template<typename ReceiverTy, typename... HandlerFuncArgs>
inline void EventObject::NotifyEventImpl( uint32_t eventHash, HandlerFuncArgs... eventArgs )
{
	// Does exist subscriber?
	auto iter = ms_globalEventListenerRepo.find( eventHash );
	if ( iter != ms_globalEventListenerRepo.end( ))
	{
		// Then, iterate the repository and notify event to them
		for ( auto& listener : iter->second )
		{
			static_cast<EventObserverImpl<Dummy>*>( listener.second )->Notify<HandlerFuncArgs...>( eventArgs... );
		}
	}
}


} /*namespace tgon*/

