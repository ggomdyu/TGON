#pragma once
#include <Engine/Executable/TGameBody.h>
#include <Engine/Module/InputModule.h>
#include <Console/TConsole.h>



using namespace tgon;


//TGON_GENERATE_EVENT( OnDestroy )


class TgonModelJoy :
	public TGameBody
{

/*
	Generator
*/
public:
	TGON_GENERATE_OBJECT_INTERFACE( TgonModelJoy, TGameBody )

/*
	Cons/Destructor
*/
public:
	TgonModelJoy( ) :
		TGameBody( WindowStyle::DefaultStyle, GraphicsProperty{} )
	{
		this->SubscribeEvent( TEventType( "OnDestroy" ), &TgonModelJoy::OnDestroy );
	}

	void OnDestroy( )
	{
	}

//	virtual void Update( ) override
//	{
//	}
};

