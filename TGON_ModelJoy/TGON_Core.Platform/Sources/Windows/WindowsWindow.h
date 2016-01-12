/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� : ����ȣ
* ���� ������ : 2015-01-09
*/

#pragma once
#include "IWindowImplBase.h"

#include <Windows.h>
#include <iostream>


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
	void					CreateWindowForm( const WindowStyle& );
	static LRESULT		WINAPI CallbackMsgProc( HWND, unsigned int, WPARAM, LPARAM );

	// Overridable message procedure
	virtual LRESULT		WINAPI CustomMsgProc( HWND, unsigned int, WPARAM, LPARAM );
		 
private:
	MSG		m_msg;
	HWND	m_wndHandle;
};


}