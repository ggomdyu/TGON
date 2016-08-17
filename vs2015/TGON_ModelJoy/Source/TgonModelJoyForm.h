#pragma once
#include <Platform/Console/TConsole.h>
#include <Engine/Executable/TGameBody.h>
#include <Engine/Object/TCoreEvents.h>


using namespace tgon;




class TgonModelJoy :
	public TGameApplication
{
	int n = 3;
/*
	Generator
*/
public:
	TGON_GENERATE_OBJECT_INTERFACE( TgonModelJoy, TGameApplication )

/*
	Cons/Destructor
*/
public:
	TgonModelJoy( )
	{
		this->SubscribeEvent<E_DESTROY>( &This::OnDestroy );
		this->SubscribeEvent<E_BEGINUPDATE>( &This::OnUpdate );
	}

	void OnUpdate( int n )
	{
		MessageBoxA( 0, "BEGIN UPDATE", 0, 0 );
	}

	void OnDestroy( )
	{
		MessageBoxA( 0, "DESTROY", 0, 0 );
	}
};