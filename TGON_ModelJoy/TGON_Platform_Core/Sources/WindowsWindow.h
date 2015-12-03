/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "GenericWindow.h"

#ifndef TGON_USE_PRECOMPILED_HEADER
	#define WIN32_LEAN_AND_MEAN /* fwd declare */
	#include <Windows.h>
#endif

NSBEGIN( tgon );
class WindowsWindow;
typedef WindowsWindow Window;

class WindowsWindow final : public GenericWindow
{
public:
	explicit WindowsWindow( _In_ const WindowStyle& );
	virtual ~WindowsWindow( );

public:
	virtual void Make( ) override;

	HWND GetWindowHandle( ) const;
	
public:
	/* Show */
	virtual void BringToTop( ) override;
	virtual void Show( ) override;

	/* Move, animate, etc... */
	virtual void SetPosition( const int x, const int y ) override;
	virtual void Move( const int x, const int y ) override;

private:
	static LRESULT CALLBACK CallbackMsgProc( HWND, uint32_t, WPARAM, LPARAM );
	LRESULT CALLBACK CustomMsgProc( HWND, uint32_t, WPARAM, LPARAM );

private:
	HWND m_wndHandle;
};
NSEND( );