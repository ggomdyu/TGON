#pragma once
#include <Engine/Executable/TGameBody.h>
#include <Engine/Module/InputModule.h>
#include <Console/TConsole.h>



using namespace tgon;


TGON_GENERATE_EVENT( E_DESTROY, int )


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
		this->SubscribeEvent<E_DESTROY>( &This::OnDestroy );
		this->NotifyEvent<E_DESTROY, This>( 3 );
	}

	void OnDestroy( int )
	{
		MessageBox( 0,0,0,0 );
	}

//	virtual void Update( ) override
//	{
//	}
};

