/*
* Author : Cha Junho
* Date : 06/02/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <Object/TEventSubject.h>
#include <Graphics/TGraphics.h>
#include <Application/TApplication.h>

#include "TgonModelJoyForm.h"


namespace tgon
{


class Program
{
public:
	static int32_t Main( )
	{
		// Make window as default style
		auto window = std::make_shared<TgonModelJoyForm>( );

		return TApplication::Run( *window.get( ));
	}
};


}