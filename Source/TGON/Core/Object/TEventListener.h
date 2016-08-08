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

//
// Listen some event and inform to subject 
//
class TEventListener :
	public tgon::TObject
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( TEventListener, std::nullptr_t )


public:
/*
	Cons/Destructor
*/
	explicit TEventListener( tgon::TEventSubject* receiver ) :
		m_receiver( receiver )
	{
		assert( receiver );
	}


public:
/*
	Commands
*/
	//virtual void Notify( ) = 0;


/*
	Gets
*/
	tgon::TEventSubject* GetReceiver( )
	{
		return m_receiver;
	}


private:
	tgon::TEventSubject* m_receiver;
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
	TEventListenerImpl( tgon::TEventSubject* receiver, HandlerFunction eventHandlerFunc ) :
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


}