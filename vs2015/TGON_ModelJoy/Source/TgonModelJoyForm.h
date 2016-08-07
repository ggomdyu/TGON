#pragma once
#include <Engine/Executable/TGameBody.h>
#include <Console/TConsole.h>

using namespace tgon;


class TgonModelJoy :
	public TGameBody
{

/*
	Generator
*/
public:
	TGON_OBJECT( TgonModelJoy, TGameBody )

/*
	Cons/Destructor
*/
public:
	TgonModelJoy( ) :
		TGameBody( WindowStyle::DefaultStyle, GraphicsProperty{} )
	{
	}

	void OnUpdateBegin( )
	{
		
	}

//	virtual void Update( ) override
//	{
//	}
};

