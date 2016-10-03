#pragma once
#include <Core/Platform/PlatformApplication.h>
#include <Core/Platform/PlatformTime.h>
#include <Core/Platform/PlatformConsole.h>
#include <Engine/GameApplication.h>
#include <Engine/CoreEvents.h>
#include <Core/Template/Cast.h>
#include <Core/Object/Type.h>
#include <Core/Delegate/Delegate.h>


using namespace tgon;

Delegate<void( int32_t, int32_t )> g_delegate;

class MyCustomWindow :
	public TWindowFrame
{
public:
	using TWindowFrame::TWindowFrame;

public:
	virtual void OnMouseDown( int32_t x, int32_t y, MouseType mouseType ) override
	{
		g_delegate( x, y );
	}

	// 
	// Event handlers
	// 
	virtual bool OnDestroy( ) override
	{
		return MessageBox( NULL, L"Are you sure you want to quit?", L"WARNING!", MB_YESNO ) == IDYES;
	}
};

TGON_GENERATE_EVENT( E_FOO, int )

class TGONSample :
	public GameApplication
{
public:
	// 
	// Generator
	// 
	TGON_GENERATE_OBJECT_INTERFACE( TGONSample, GameApplication )

public:
	// 
	// Ctor/Dtor
	// 
	TGONSample( ) :
		GameApplication( MakeWindow<MyCustomWindow>( WindowStyle::DefaultStyle ))
	{
		g_delegate = TGON_MAKE_DELEGATE( void( int32_t, int32_t ), &TGONSample::MyFunction, this );
	};


public:
	//
	// Commands
	//
	virtual ~TGONSample( )
	{
	}

	void MyFunction( int32_t x, int32_t y )
	{
		std::string str = ( std::to_string( x ) + " " + std::to_string( y ) + "          " );
		MessageBoxA( 0, str.c_str(), 0, 0 );
	}

	virtual void OnUpdate( ) override
	{
	}
};