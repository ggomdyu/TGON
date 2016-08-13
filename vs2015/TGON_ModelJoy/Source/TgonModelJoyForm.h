#pragma once
#include <Engine/Executable/TGameBody.h>
#include <Engine/Module/InputModule.h>
#include <Console/TConsole.h>



using namespace tgon;



class TgonModelJoy :
	public TGameApplication
{

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
//		this->SubscribeEvent<E_DESTROY>( &This::OnDestroy );
		//this->SubscribeEvent<E_UPDATE>( &This::OnUpdate );
	}
	

	void OnUpdate( int param )
	{
	}

	void OnDestroy( )
	{
	}

//	virtual void Update( ) override
//	{
//	}
};