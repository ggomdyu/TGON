/*
* Author : Cha Junho
* Date : 07/10/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "TEventListener.h"
#include "TType.h"


#define TGON_GENERATE_EVENT( eventName )\
namespace tgon\
{\
	namespace TEvent\
	{\
		tgon::TEventType eventName( #eventName );\
	}\
}

namespace tgon
{


using TEventType = TType;

class TGON_API TEventSubject :
	public TObject
{
/*
	Type definitions
*/
	template <typename ReceiverTy>
	using HandlerFunction = void( ReceiverTy::* )( );

	using ListenerRepo = std::unordered_map<TEventSubject*, TEventListener*>;
	
	// uint32_t is TEventType's hash code.
	// ListenerRepo is the subscriber list of this event.
	using EventListenerRepo = std::unordered_map<uint32_t, ListenerRepo>;

	
/*
	Generator
*/
public:
	TGON_GENERATE_OBJECT_INTERFACE( TEventSubject, std::nullptr_t )


public:
	/*
		Commands
	*/
	//
	// Subscribe specific event's handling. 
	//
	// @param eventType Specify what you want to subscribe
	// @param handlerFunction Set Event handler function. It will be invoken when event handled
	//
	template<typename ReceiverTy>
	void SubscribeEvent( TEventType eventType, HandlerFunction<ReceiverTy> handlerFunction );

	//
	// Unsubscribe specific event that this object subscribed
	//
	// @param eventType Specify what you want to unsubscribe event
	//
	void UnsubscribeEvent( TEventType eventType );

	//
	// Unsubscribe all of events this object subscribed
	//
	void UnsubscribeAllEvents( );


/*
	Cons/Destructor
*/
public:
	TEventSubject( ) = default;

	virtual ~TEventSubject( );


/*
	Protect functions
*/
protected:
	void NotifyEvent( TEventType eventType );


/*
	Private variables
*/
private:
	static EventListenerRepo ms_globalEventListenerRepo;
};


template<typename ReceiverTy>
inline void TEventSubject::SubscribeEvent( TEventType eventType, HandlerFunction<ReceiverTy> handlerFunction )
{
	ms_globalEventListenerRepo[eventType.GetHashCode( )][this] = new TEventListenerImpl<ReceiverTy>( this, handlerFunction );
}


}