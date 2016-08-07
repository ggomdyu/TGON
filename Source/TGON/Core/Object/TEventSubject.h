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
	TGON_OBJECT( TEventSubject, std::nullptr_t )

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
	//
	// Subscribe event. EventListener will invoke event handler on event.
	//
	// @param eventType Specify what you want to subscribe
	// @param handlerFunction Set Event handler function. It will be invoken when event handled
	//
	template<typename ReceiverTy>
	void SubscribeEvent( TEvent eventType, HandlerFunctionTy<ReceiverTy> handlerFunction );

	//
	// Unsubscribe specific event that this object subscribed
	//
	// @param eventType Specify what you want to unsubscribe event
	//
	void UnsubscribeEvent( TEvent eventType );

	//
	// Unsubscribe all of events that this object subscribed
	//
	void UnsubscribeAllEvents( );


	/*
		Protect functions
	*/
protected:
	void NotifyEvent( TEvent eventType );


	/*
		Private variables
	*/
private:
	// It Includes global event subscription info ( e.g. Input, BeginUpdate, ... )
	static EventMap ms_globalMap;
};


template<typename ReceiverTy>
inline void TEventSubject::SubscribeEvent( TEvent eventType, HandlerFunctionTy<ReceiverTy> handlerFunction )
{
	ms_globalMap[eventType][this] = new TEventListenerImpl<ReceiverTy>( this, handlerFunction );
}


}