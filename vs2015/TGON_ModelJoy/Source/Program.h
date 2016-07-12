/*
* Author : Cha Junho
* Date : 06/02/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <Application/TApplication.h>
#include <Object/TEventSubject.h>
#include "TgonModelJoyForm.h"


namespace tgon
{


class Program
{
public:
	static int32_t Main( )
	{
		// Make window as default style
		auto window = TWindow::Make( WindowStyle::DefaultStyle );

		return TApplication::Run( *window.get( ));
	}
};


}