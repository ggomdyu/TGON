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
	OnUpdateBegin,
	OnUpdateEnd,
	OnRenderBegin,
	OnRenderEnd,
	OnDestroy,
};


class TGON_API TEventSubject :
	public TObject
{
	template <typename ReceiverTy>
	using HandlerFunctionTy = void( ReceiverTy::* )( );

	using ListenerMap = std::unordered_map<TEventSubject*, TEventListener*>;
	
	using EventMap = std::unordered_map<TEvent, ListenerMap>;


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
	template<typename ReceiverTy>
	void SubscribeEvent( TEvent eventType, HandlerFunctionTy<ReceiverTy> eventListener );

	// Unsubscribe specific event that this object subscribed
	void UnsubscribeEvent( TEvent eventType );

	// Unsubscribe all of events that this object subscribed
	void UnsubscribeAllEvents( );

protected:
	void NotifyEvent( TEvent eventType );


private:
	// It Includes global event subscription info ( e.g. Input, BeginUpdate, ... )
	static EventMap ms_globalMap;
};


template<typename ReceiverTy>
inline void TEventSubject::SubscribeEvent( 
	TEvent eventType, 
	HandlerFunctionTy<ReceiverTy> eventListener )
{
	ms_globalMap[eventType][this] = new TEventListenerImpl<ReceiverTy>( this, eventListener );
}


}