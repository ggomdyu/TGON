/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 : 차준호
* 최종 수정일 : 2015-01-09
*/

#pragma once
#include "IWindow.h"

#include <Windows.h>
#include <iostream>


namespace tgon {


class WindowsWindowDeliverable;
typedef WindowsWindowDeliverable WindowImpl;

class WindowsWindowDeliverable : public IWindow
{
public:
	explicit			WindowsWindowDeliverable( const WindowStyle& = WindowStyle( ));
	virtual				~WindowsWindowDeliverable( );

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
	void					CreateWindowForm( const WindowStyle& );
	static LRESULT		WINAPI CallbackMsgProc( HWND, unsigned int, WPARAM, LPARAM );

	// Overridable message procedure
	virtual LRESULT		WINAPI CustomMsgProc( HWND, unsigned int, WPARAM, LPARAM );
		 
private:
	MSG		m_msg;
	HWND	m_wndHandle;
};


}