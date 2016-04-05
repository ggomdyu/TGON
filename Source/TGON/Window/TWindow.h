/*
* 작성자 : 차준호
* 작성일 : 2015/11/12
* 최종 수정 : 
* 최종 수정일 : 
* Description : Polymorphic window type
*/

#pragma once
#include <iostream>
#include "../Config/Platform/PlatformWindow.h"
#include "../Window/WindowStyle.h"
#include "../Console/TConsole.h"

namespace tgon
{


class TWindow;
using SpTWindow = std::shared_ptr<TWindow>;

class TWindow : public WindowImpl
{
public:
	// Factory
	static SpTWindow Create( const WindowStyle& wndStyle = WindowStyle( ));

	/*
		@ Cons/Destructors
	*/
public:
	virtual ~TWindow( );
private:
	explicit TWindow( const struct WindowStyle& wndStyle );
	explicit TWindow( const TWindow& ) = delete;
	TWindow& operator=( const TWindow& ) = delete;
};


inline SpTWindow TWindow::Create( const WindowStyle& wndStyle )
{
	std::shared_ptr<TWindow> ptr( new TWindow( wndStyle ));
	return ptr;
}


}