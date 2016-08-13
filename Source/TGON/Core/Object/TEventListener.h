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
	
*/
public:
	virtual void OnCreate( );

	virtual void OnUpdate( );

	virtual void OnDestroy( );

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
	//
	// This class will notify to receiver when event handled.
	//
	// @param receiver Event handling receiver
	//
	explicit TEventListener( TEventSubject* receiver );
	
	//
	// Destructor
	//
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

	virtual ~TEventListenerImpl( )
	{
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