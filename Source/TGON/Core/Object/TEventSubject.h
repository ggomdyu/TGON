/*
* Author : Cha Junho
* Date : 07/10/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "TEventListener.h"


namespace tgon
{


enum TEvent
{
	OnSpaceDown,
	OnEscDown,
};


class TGON_API TEventSubject :
	public TObject
{
	template <typename _ReceiverTy>
	using _HandlerFunctionTy = void( _ReceiverTy::* )( );

	using _ListenerMapTy = std::unordered_map<TEventSubject*, TEventListener*>;
	
	using _EventMapTy = std::unordered_map<TEvent, _ListenerMapTy>;


public:
	TGON_OBJECT( TEventSubject, TObject )

public:
	/*
		Cons/Destructor
	*/
	TEventSubject( ) = default;

	virtual ~TEventSubject( );


public:
	/*
		Commands
	*/
	// Subscribe event. EventListener will invoke event handler on event.
	template<typename _ReceiverTy>
	void SubscribeEvent( TEvent eventType, _HandlerFunctionTy<_ReceiverTy> eventListener );

	// Unsubscribe specific event that this object subscribed
	void UnsubscribeEvent( TEvent eventType );

	// Unsubscribe all of events that this object subscribed
	void UnsubscribeAllEvents( );

protected:
	void NotifyEvent( TEvent eventType );


private:
	// It Includes global event subscription info ( e.g. Input, BeginUpdate, ... )
	static _EventMapTy ms_globalMap;
};


template<typename _ReceiverTy>
inline void TEventSubject::SubscribeEvent( 
	TEvent eventType, 
	_HandlerFunctionTy<_ReceiverTy> eventListener )
{
	ms_globalMap[eventType][this] = new TEventListenerImpl<_ReceiverTy>( this, eventListener );
}


}