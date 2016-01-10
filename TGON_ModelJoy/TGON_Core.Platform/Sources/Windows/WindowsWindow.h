/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 : 차준호
* 최종 수정일 : 2015-01-09
*/

#pragma once
#include "IWindowImplBase.h"

#include <Windows.h>
#include <iostream>
#include "WindowEvent.h"
#include "WindowStyle.h"


namespace tgon {


class WindowsWindow;
using WindowImpl = WindowsWindow;

class WindowsWindow : public IWindowImplBase
{
public:
	explicit			WindowsWindow( const WindowStyle& = WindowStyle( ));
	virtual				~WindowsWindow( );

	virtual void		FrameMove( ) override;
		
public:
	virtual void		Show( ) override;
	virtual void		BringToTop( ) override;
	virtual void		SetPosition( int x, int y ) override;
	virtual void		Move( int x, int y ) override;
	virtual void		Exit( ) override;

public:
	HWND								GetWindowHandle( ) const				{ return m_wndHandle; }
	virtual const WindowEvent		GetWindowEvent( ) const override	{ return m_msg.message; }

private:
	void					MakeWindow( const WindowStyle& );
	static LRESULT		WINAPI CallbackMsgProc( HWND, uint32_t, WPARAM, LPARAM );

	// Overridable message procedure
	virtual LRESULT		WINAPI CustomMsgProc( HWND, uint32_t, WPARAM, LPARAM );
		 
private:
	MSG		m_msg;
	HWND	m_wndHandle;
};


}