/*
* Author : Cha Junho
* Date : 07/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "Object.h"


namespace tgon
{


class EventObject;
class EventObserver
{
	//
	// Ctor/Dtor
	//
public:
	/*
	 * @note	This class will notify to receiver when event handled.
	 * @param	receiver Event handling receiver
	*/
	explicit EventObserver( EventObject* receiver );
	virtual ~EventObserver( ) = 0;

	//
	// Gets
	//
public:
	EventObject* GetObserver( );

	//
	// Private variables
	//
private:
	EventObject* m_receiver;
};


template <class ReceiverTy>
class TGON_API EventObserverImpl :
	public EventObserver
{
	template <typename... HandlerFuncArgs>
	using HandlerFunction = void( ReceiverTy::* )( HandlerFuncArgs... );

	// 
	// Ctor/Dtor
	// 
public:
	EventObserverImpl( EventObject* receiver, HandlerFunction<> eventHandlerFunc );
	virtual ~EventObserverImpl( ) = default;

	// 
	// Commands
	// 
public:
	template <typename... HandlerFuncArgs>
	void Notify( HandlerFuncArgs... args );

	// 
	// Private variables
	// 
private:
	HandlerFunction<> m_eventHandlerFunc;
};


inline EventObject* EventObserver::GetObserver( )
{
	return m_receiver;
}

template<typename ReceiverTy>
inline EventObserverImpl<ReceiverTy>::EventObserverImpl( EventObject* receiver, HandlerFunction<> eventHandlerFunc ) :
	EventObserver( receiver ),
	m_eventHandlerFunc( eventHandlerFunc )
{
	assert( m_eventHandlerFunc );
}

template<class ReceiverTy>
template<typename... HandlerFuncArgs>
inline void EventObserverImpl<ReceiverTy>::Notify( HandlerFuncArgs... args )
{
	HandlerFunction<HandlerFuncArgs...> realFunc = reinterpret_cast<HandlerFunction<HandlerFuncArgs...>>( 
		m_eventHandlerFunc );

	( reinterpret_cast<ReceiverTy*>( GetObserver( ))->*realFunc )( args... );
}


} /*namespace tgon*/