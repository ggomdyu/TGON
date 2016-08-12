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


class TEventListener :
	public tgon::TObject
{
/*
	Generator
*/
public:
	TGON_GENERATE_OBJECT_INTERFACE( TEventListener, tgon::TObject )

/*
	Cons/Destructor
*/
public:
	explicit TEventListener( TEventSubject* receiver );

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

template <class ReceiverTy, typename... HandlerArgs>
class TGON_API TEventListenerImpl :
	public TEventListener
{
/*
	Type definitions
*/
	using HandlerFunction = void( ReceiverTy::* )( HandlerArgs... );


/*
	Generators
*/
public:
	TGON_GENERATE_OBJECT_INTERFACE( TEventListenerImpl<ReceiverTy>, TEventListener )


/*
	Cons/Destructor
*/
public:
	TEventListenerImpl( TEventSubject* receiver, HandlerFunction eventHandlerFunc ) :
		TEventListener( receiver ),
		m_eventHandlerFunc( eventHandlerFunc )
	{
		assert( m_eventHandlerFunc );
	}


/*
	Commands
*/
public:
	template <typename... EventHandlerArgs>
	void Notify( EventHandlerArgs&&... args )
	{
		( static_cast<ReceiverTy*>( GetReceiver( ))->*m_eventHandlerFunc )( std::forward<EventHandlerArgs>( args )... );
	}


/*
	Private variables
*/
private:
	HandlerFunction m_eventHandlerFunc;
};


inline TEventSubject* TEventListener::GetReceiver( )
{
	return m_receiver;
}


}