/*
* Author : Junho-Cha
* Date : 11/12/2015
* Latest author :
* Latest date :
* Description : Platform dependent API Sets for Windows
*/

#pragma once
#include "../Abstract/AbstractWindow.h"

#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#	undef WIN32_LEAN_AND_MEAN
#endif


namespace tgon
{

class WindowsWindow;
using WindowImpl = WindowsWindow;
using SpTWindow = std::shared_ptr<WindowImpl>;
using WpTWindow = std::weak_ptr<WindowImpl>;

class TGON_API WindowsWindow : 
	public AbstractWindow
{
protected:
	explicit WindowsWindow( const struct WindowStyle& );
	virtual ~WindowsWindow( );

public:
	/*
		Gets
	*/
	HDC GetDC( ) const;
	HWND GetWindowHandle( ) const;

private:
	void AdditionalInit( const struct WindowStyle& );

private:
	HDC m_dcHandle;
	HWND m_wndHandle;
};

inline HDC WindowsWindow::GetDC( ) const
{
	return m_dcHandle;
}

inline HWND tgon::WindowsWindow::GetWindowHandle( ) const
{
	return m_wndHandle;
}


}