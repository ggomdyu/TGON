/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 : 차준호
* 최종 수정일 : 2016-01-09
*/

#pragma once

#include "WindowStyle.h"
#include "WindowEvent.h"
#include "PlatformWindow.h"


namespace tgon {

class Window final
{
	typedef std::function<void( )> EventProc;

public:
	explicit		Window( const WindowStyle& wndStyle );
					~Window( );

	void			FrameMove( )					{ m_wndImpl.FrameMove( ); }

public:
	void			Show( )							{ m_wndImpl.Show( ); }
	void			BringToTop( )					{ m_wndImpl.BringToTop( ); }
	void			SetPosition( int x, int y )		{ m_wndImpl.SetPosition( x, y ); }
	void			Move( int x, int y )				{ m_wndImpl.Move( x, y ); }
	void			Exit( )								{ m_wndImpl.Exit( ); }

	void			AddEventCallback( uint32_t evType, const EventProc& evProc )	{ m_wndImpl.AddEventCallback( evType, evProc ); }

public:
	const WindowEvent		GetWindowEvent( ) const	{ return m_wndImpl.GetWindowEvent( ); }
	const WindowStyle&		GetWindowStyle( ) const		{ return m_wndImpl.GetWindowStyle( ); }

private:
	WindowImpl	m_wndImpl;
};


}