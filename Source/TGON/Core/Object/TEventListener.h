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


class TGON_API TEventListener :
	public TObject
{
public:
	TGON_OBJECT( TEventListener, std::nullptr_t )


public:
	/*
		Cons/Destructor
	*/
	explicit TEventListener( class TEventSubject* receiver ) :
		m_receiver( receiver )
	{
		assert( receiver );
	}


public:
	/*
		Commands
	*/
	virtual void Notify( ) = 0;
	

	/*
		Gets
	*/
	class TEventSubject* GetReceiver( )
	{
		return m_receiver;
	}


private:
	class TEventSubject* m_receiver;
};


template <class ReceiverTy>
class TGON_API TEventListenerImpl :
	public TEventListener
{
	using HandlerFunctionTy = void( ReceiverTy::* )( );


public:
	TGON_OBJECT( TEventListenerImpl<ReceiverTy>, TEventListener )


public:
	/*
		Cons/Destructor
	*/
	TEventListenerImpl( class TEventSubject* receiver, HandlerFunctionTy eventHandlerFunc ) :
		TEventListener( receiver ),
		m_handlerFunction( eventHandlerFunc )
	{
		assert( m_handlerFunction );
	}


public:
	/*
		Commands
	*/
	virtual void Notify( ) override
	{
		( static_cast<ReceiverTy*>( GetReceiver( ))->*m_handlerFunction )( );
	}


private:
	HandlerFunctionTy m_handlerFunction;
};


}