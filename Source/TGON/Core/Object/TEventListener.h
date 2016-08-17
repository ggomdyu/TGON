/*
* Author : Cha Junho
* Date : 07/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "TObject.h"


namespace tgon
{


class TEventSubject;

class TEventListener
{
/*
	Cons/Destructor
*/
public:
	//
	// @note This class will notify to receiver when event handled.
	// @param receiver Event handling receiver
	//
	explicit TEventListener( TEventSubject* receiver );
	
	virtual ~TEventListener( ) = 0;

/*
	Gets
*/
public:
	TEventSubject* GetReceiver( );

/*
	Private variables
*/
private:
	TEventSubject* m_receiver;
};

inline TEventSubject* TEventListener::GetReceiver( )
{
	return m_receiver;
}


template <class ReceiverTy>
class TGON_API TEventListenerImpl :
	public TEventListener
{
/*
	Type definitions
*/
	template <typename... HandlerFuncArgs>
	using HandlerFunction = void( ReceiverTy::* )( HandlerFuncArgs... );

/*
	Cons/Destructor
*/
public:
	template <typename... HandlerFuncArgs>
	TEventListenerImpl( TEventSubject* receiver, HandlerFunction<HandlerFuncArgs...> eventHandlerFunc );

	virtual ~TEventListenerImpl( ) = default;

/*
	Commands
*/
public:
	template <typename... HandlerFuncArgs>
	void Notify( HandlerFuncArgs&&... args )
	{
		HandlerFunction<HandlerFuncArgs...> realFunc = reinterpret_cast<HandlerFunction<HandlerFuncArgs...>>( 
			m_eventHandlerFunc );

		( reinterpret_cast<ReceiverTy*>( GetReceiver( ))->*realFunc )(
			std::forward<HandlerFuncArgs>( args )... );
	}

/*
	Private variables
*/
private:
	HandlerFunction<> m_eventHandlerFunc;
};


template<typename ReceiverTy>
template<typename... HandlerFuncArgs>
inline TEventListenerImpl<ReceiverTy>::TEventListenerImpl( TEventSubject* receiver, HandlerFunction<HandlerFuncArgs...> eventHandlerFunc ) :
	TEventListener( receiver ),
	m_eventHandlerFunc( eventHandlerFunc )
{
	assert( m_eventHandlerFunc );
}


}