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
#include "../../Platform/Slate/PlatformWindow.h"


namespace tgon
{


using SpTWindow = std::shared_ptr<class TWindow>;
using WpTWindow = std::weak_ptr<class TWindow>;
using TMsgCallback = int32_t(*)( class TWindow*, enum class WindowEvent );


class TGON_API TWindow : public WindowImpl
{
public:
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