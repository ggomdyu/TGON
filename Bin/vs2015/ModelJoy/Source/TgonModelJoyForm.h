#pragma once
#include <Core/Platform/PlatformApplication.h>
#include <Core/Platform/PlatformTime.h>
#include <Core/Platform/PlatformConsole.h>
#include <Core/Template/Cast.h>
#include <Core/Object/Type.h>
#include <Core/Delegate/Delegate.h>
#include <Engine/GameApplication.h>
#include <Engine/CoreEvents.h>


using namespace tgon;

struct E_TEST { enum { value = 231, }; };

std::map<uint32_t, std::vector<void*>> g_listers;

struct EventObjectListener
{
public:
	EventObjectListener( ) :
		m_receiver( nullptr )
	{

	}

	void Notify( )
	{

	}

private:
	EventObject* m_receiver;
};

template <typename ReceiverTy, void( ReceiverTy::*Handler )( /*Args*/ )>
inline void SubscribeEvent( E_TEST, ReceiverTy* receiver )
{
	// Make delegate
	auto d = Delegate<void(/*Args*/)>::Bind<ReceiverTy, Handler>( receiver );
	
	// Then push to lister repo
	g_listers[E_TEST::value].push_back( receiver );

	//auto d = TGON_MAKE_DELEGATE( void( /*Args*/ ), Handler, reveiver );

}


class MyCustomWindow :
	public TWindowFrame
{
public:
	using TWindowFrame::TWindowFrame;

public:
	virtual void OnMouseDown( int32_t x, int32_t y, MouseType mouseType ) override
	{
	}

	// 
	// Event handlers
	// 
	virtual bool OnDestroy( ) override
	{
		return MessageBox( NULL, L"Are you sure you want to quit?", L"WARNING!", MB_YESNO ) == IDYES;
	}
};

void OnUpdate( )
{

}

class TGONSample :
	public GameApplication
{
	// 
	// Generator
	// 
public:
	TGON_GENERATE_OBJECT_INTERFACE( TGONSample, GameApplication )

	// 
	// Ctor/Dtor
	// 
public:
	TGONSample( ) :
		GameApplication( MakeWindow<MyCustomWindow>( WindowStyle::DefaultStyle ))
	{
		::SubscribeEvent<This, &This::OnDestroy>( E_TEST{}, this );

		//this->SubscribeEvent<E_DESTROY>( &This::OnDestroy );
		//this->NotifyEvent<E_DESTROY>( );
	};

	//
	// Commands
	//
public:
	virtual ~TGONSample( )
	{
	}

	void OnDestroy( )
	{
		MessageBox( 0, 0, 0, 0 );
	}

	//
	// Event handler
	//
public:
	virtual void OnUpdate( ) override
	{
		//⚾ -> baseball
	}
};