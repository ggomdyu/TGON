#pragma once
#include <Core/Platform/OSAL/PlatformApplication.h>
#include <Core/Platform/OSAL/PlatformTime.h>
#include <Core/Platform/OSAL/PlatformConsole.h>
#include <Core/Template/Cast.h>
#include <Core/Object/Type.h>
#include <Core/Delegate/Delegate.h>
#include <Engine/GameApplication.h>
#include <Engine/CoreEvents.h>


using namespace tgon;

struct E_TEST { enum { value = 231, }; };

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


namespace detail
{

template <typename Ty>
std::map<uint32_t, Delegate<Ty>>& GetEventListener( )
{
	static std::map<uint32_t, Delegate<void( )>> instance;
	return instance;
}

}

template <typename ReceiverTy, void( ReceiverTy::*Handler )( /*Args*/ )>
inline void SubscribeEvent( E_TEST, ReceiverTy* receiver )
{
	// Make delegate
	auto d = Delegate<void(/*Args*/)>::Bind<ReceiverTy, Handler>( receiver );
	
	// Then push to lister repo
	detail::GetEventListener<void()>()[E_TEST::value] = d;
}

template <typename EventTy, typename... Args>
inline void NotifyEvent( Args... args )
{
	GetEventListener<void( Args... )>()[EventTy::value]( args... );
}

class MyCustomWindow :
	public WindowFrame
{
public:
	using WindowFrame::WindowFrame;

public:
	virtual void OnMouseDown( int32_t x, int32_t y, MouseType mouseType ) override
	{
	}

	virtual void OnRawMouseDown( int32_t x, int32_t y, MouseType mouseType ) override
	{
		tgon::Console::Write( L"%d, %d\n", x, y );
	}
	
	virtual bool OnDestroy( ) override
	{
		return MessageBox( NULL, L"Are you sure you want to quit?", L"WARNING!", MB_YESNO ) == IDYES;
	}
};

//struct E_DESTROY {};
//struct E_CREATE {};
//
//void FooImpl( E_DESTROY, int ) {}
//
//template <typename EvTy, typename... Args>
//void Foo( Args... args )
//{
//	FooImpl( EvTy{}, args... );
//}

class TGONSample :
	public GameApplication
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( TGONSample, GameApplication )

public:
	TGONSample( ) :
		GameApplication( MakeWindow<MyCustomWindow>( WindowStyle{} ) )
	{
		this->GetRootWindow( )->EnableGlobalInputHook( 
			true, RawInputType::kMouse );
	};

public:
	virtual ~TGONSample( )
	{
	}

public:
	virtual void OnRender( ) override
	{

	}

	virtual void OnUpdate( ) override
	{
		//⚾ -> baseball
	}
};