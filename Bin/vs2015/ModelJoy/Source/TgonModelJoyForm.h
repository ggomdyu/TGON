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

class MyCustomWindow :
	public TWindowFrame
{
public:
	using TWindowFrame::TWindowFrame;

public:
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
	};


public:
	//
	// Commands
	//
	virtual ~TGONSample( )
	{
	}

	virtual void OnUpdate( ) override
	{
	}
};