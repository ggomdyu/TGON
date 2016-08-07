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
class TGON_API TEventListener :
	public TObject
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( TEventListener, std::nullptr_t )


public:
	/*
		Cons/Destructor
	*/
	explicit TEventListener( TEventSubject* receiver );


public:
	/*
		Commands
	*/
	virtual void Notify( ) = 0;
	

	/*
		Gets
	*/
	TEventSubject* GetReceiver( )
	{
		return m_receiver;
	}


private:
	TEventSubject* m_receiver;
};


template <class ReceiverTy>
class TGON_API TEventListenerImpl :
	public TEventListener
{
	using HandlerFunctionTy = void( ReceiverTy::* )( );


public:
	TGON_GENERATE_OBJECT_INTERFACE( TEventListenerImpl<ReceiverTy>, TEventListener )


/*
	Cons/Destructor
*/
public:
	TEventListenerImpl( TEventSubject* receiver, HandlerFunctionTy eventHandlerFunc );


public:
	/*
		Commands
	*/
	virtual void Notify( ) override
	{
		( static_cast<ReceiverTy*>( GetReceiver( ))->*m_eventHandlerFunc )( );
	}


private:
	HandlerFunctionTy m_eventHandlerFunc;
};


template <class ReceiverTy>
inline tgon::TEventListenerImpl<ReceiverTy>::TEventListenerImpl( TEventSubject* receiver, HandlerFunctionTy eventHandlerFunc ) :
	TEventListener( receiver ),
	m_eventHandlerFunc( eventHandlerFunc )
{
	assert( m_eventHandlerFunc );
}


}