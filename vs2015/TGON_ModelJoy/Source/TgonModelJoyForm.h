#pragma once
#include <Engine/Executable/TGameBody.h>
#include <Console/TConsole.h>

using namespace tgon;

#define TGON_GENARATE_EVENT


//const uint32_t OnDestroy


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
		this->SubscribeEvent( );
	}

	void OnUpdateBegin( )
	{
		
	}

//	virtual void Update( ) override
//	{
//	}
};

