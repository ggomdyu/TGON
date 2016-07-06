#pragma once

#include <Window/TWindow.h>
#include <Graphics/TGraphics.h>
#include <Console/TConsole.h>
#include <Screen/TScreen.h>
#include <Reflection/TObject.h>

namespace tgon
{


class TgonModelJoyForm :
	public TWindow
{
public:
	TgonModelJoyForm( ) :
		TWindow( WindowStyle::LoadFromXML( "WindowStyle.xml" ))
	{
	}

	~TgonModelJoyForm( )
	{
	}

	virtual void OnIdle( ) override
	{
	}

	virtual void OnLMouseDown( int32_t x, int32_t y )
	{
		class A : public TObject { public: TGON_OBJECT( A, std::nullptr_t ) };
		class B : public A { public: TGON_OBJECT( B, A ) };
		class C : public B { public: TGON_OBJECT( C, B ) };

		B* b = new C;
	}
};


}