/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 : 차준호
* 최종 수정일 : 2015-01-09
*/

#pragma once
#include "IWindow.h"
#include "WindowStyle.h"

#include <Windows.h>
#include <iostream>


namespace tgon {
namespace Window {

class WindowsWindow;
typedef WindowsWindow WindowImpl;


class WindowsWindow : public IWindow
{
public:
	/*
		- What's the Eventable system?

		It's a function that polling window message that arised each frames.
		If you do not use this, you can check only global message that can bring by 'DispatchWindowEvent'.
		Instead, Application will get some degree of performance improvements.
	*/

	explicit	WindowsWindow( bool isEventable, const WindowStyle& = WindowStyle( ));
	virtual		~WindowsWindow( );
		
public:
	virtual void		Show( ) override;
	virtual void		BringToTop( ) override;
	virtual void		SetPosition( const int x, const int y ) override;
	virtual void		Move( const int x, const int y ) override;
	virtual void		Exit( ) override;

	virtual void		GetPosition( int* x, int* y ) override;
	HWND			GetWindowHandle( ) const				{ return m_wndHandle; }

private:
	void	CreateWindowForm( const WindowStyle& );
	
	static LRESULT		WINAPI CallbackMsgProc( HWND, UINT, WPARAM, LPARAM );
	virtual LRESULT		WINAPI CustomMsgProc( HWND, UINT, WPARAM, LPARAM );
		 
private:
	MSG		m_msg;
	HWND	m_wndHandle;
};


}
}