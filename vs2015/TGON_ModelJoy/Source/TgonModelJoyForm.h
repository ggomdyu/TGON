#pragma once

#include <Window/TWindow.h>
#include <Graphics/TGraphics.h>
#include <Console/TConsole.h>
#include <Screen/TScreen.h>
#include <Object/TObject.h>
#include <Object/TEventListener.h>

namespace tgon
{

	class W :
		public TEventSubject
	{
	public:
//		TGON_OBJECT( W, TEventSubject )

	public:
		W( )
		{
//			this->SubscribeEvent( TEvent::OnEscDown, &W::P );
		}


		void P( )
		{

		}
	};


class TgonModelJoyForm :
	public TWindow
{
public:
	TgonModelJoyForm( ) :
		TWindow( WindowStyle::LoadFromXML( "WindowStyle.xml" ))
	{
		W w;
	}

	~TgonModelJoyForm( )
	{
	}

	virtual void OnIdle( ) override
	{
	}

	virtual void OnLMouseDown( int32_t x, int32_t y )
	{
	}
};


}