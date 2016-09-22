#pragma once
#include <Platform/OSAL/PlatformApplication.h>
#include <Platform/OSAL/PlatformTime.h>
#include <Platform/OSAL/PlatformConsole.h>
#include <Engine/GameApplication.h>
#include <Engine/CoreEvents.h>
#include <Core/Template/Cast.h>


using namespace tgon;

class EngineWindowEventHandler :
	public AWindowEventHandler
{
public:
	// 
	// Event handlers
	// 
	virtual bool OnDestroy( )
	{

		//TPlatformConsole::Get( ).WriteLine( "OnDestroy" );
		return MessageBox( NULL, L"Are you sure you want to quit?", L"WARNING!", MB_YESNO ) == IDYES;
	}

	virtual bool OnGetFocus( ) override
	{
		//TPlatformConsole::Get( ).WriteLine( "OnGetFocus" );
		return false;
		//platform::TApplication::Get()->GetRootWindow( )->BringToTop();
	}

	virtual bool OnLoseFocus( ) override
	{
		//TPlatformConsole::Get( ).WriteLine( "OnLoseFocus" );
		return false;
	}

	// 
	// Ctor/Dtor
	// 
public:
	EngineWindowEventHandler( ) = default;
	virtual ~EngineWindowEventHandler( ) = default;
};


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
		GameApplication( WindowStyle::LoadFromXML( "WindowStyle.xml" ))
	{
		this->SubscribeEvent<E_DESTROY>( &This::OnDestroy );
		this->GetRootWindow( )->SetEventHandler( std::make_shared<EngineWindowEventHandler>( ));
	}

	virtual void Update( )
	{
	}

	void OnBeginUpdate( )
	{
	}

	void OnDestroy( )
	{

	}

};