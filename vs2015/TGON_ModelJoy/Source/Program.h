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



class W :public TEventSubject
{
public:
	W( )
	{
		this->SubscribeEvent( TEvent::OnEscDown, &W::A );
	}

	void A( )
	{
		MessageBox( 0, 0, 0, 0 );
	}
};

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