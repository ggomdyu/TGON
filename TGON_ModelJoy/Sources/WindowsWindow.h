/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "GenericWindow.h"

struct CDwExStyle;
struct CDwStyle;

NSBEGIN( tgon );
class WindowsWindow;
typedef WindowsWindow PlatformWindow;

class WindowsWindow : public GenericWindow
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
	
protected:
	bool RegisterWindow( _In_ const WindowStyle&,
						_In_opt_ const HICON = LoadIcon( NULL, IDI_APPLICATION ),
						_In_opt_ const HCURSOR = LoadCursor( NULL, IDC_ARROW ));

private:
	static LRESULT CALLBACK MsgBaseProc( HWND, uint32_t, WPARAM, LPARAM );
	LRESULT CALLBACK MsgDelivedProc( HWND, uint32_t, WPARAM, LPARAM );

private:
	HWND m_hWnd;
};
NSEND( );