#pragma once
#include <Engine/Executable/TGameBody.h>
#include <Console/TConsole.h>

using namespace tgon;


class TgonModelJoy :
	public TGameBody
{
public:
	TgonModelJoy( ) :
		TGameBody( WindowStyle::DefaultStyle )
	{
	}

	void OnUpdateBegin( )
	{
		
	}
};

