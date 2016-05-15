/*
* Author : Junho-Cha
* Date : 11/12/2015
* Latest author : 
* Latest date : 
* Description : Polymorphic window type
*/

#pragma once
#include <memory>
#include <stdint.h>
#include "../Platform/PlatformWindow.h"


namespace tgon
{


class TWindow;
using SpTWindow = std::shared_ptr<TWindow>;
using WpTWindow = std::weak_ptr<TWindow>;

using TMsgCallback = int32_t(*)( TWindow*, enum class WindowEvent );


class TGON_API TWindow : public WindowImpl
{
public:
	TGON_OBJECT( TWindow, WindowImpl )

	static SpTWindow Create( const WindowStyle& wndStyle = WindowStyle( ));


private:
	explicit TWindow( const WindowStyle& );
public:
	virtual ~TWindow( );
};


inline SpTWindow TWindow::Create( const WindowStyle& wndStyle )
{
	std::shared_ptr<TWindow> ptr( new TWindow( wndStyle ));
	return ptr;
}


}