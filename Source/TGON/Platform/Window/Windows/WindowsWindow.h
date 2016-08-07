/*
* Author : Cha Junho
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once
#include "../Abstract/AbstractWindow.h"

#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	undef WIN32_LEAN_AND_MEAN
#endif


namespace tgon
{


struct WindowStyle;

class WindowsWindow;
using WindowImpl = WindowsWindow;


class TGON_API WindowsWindow : 
	public AbstractWindow
{
	friend class WindowsApplication;

/*
	Cons/Destructor
*/
protected:
	//
	// Constructor
	//
	explicit WindowsWindow( /*In*/ const WindowStyle& wndStyle );

	//
	// Destructor
	//
	virtual ~WindowsWindow( );

/*
	Commands
*/
public:
	virtual bool PumpEvent( ) override;

	virtual void Show( ) override;

	virtual void Hide( ) override;

	virtual void Quit( ) override;

	virtual void Maximize( ) override;

	virtual void Minimize( ) override;

	virtual void BringToTop( ) override;

	virtual void Flash( ) override;

	virtual void EnableGlobalMouseFocus( bool isEnable ) override;


/*
	Sets
*/
	virtual void SetPosition( int32_t x, int32_t y ) override;

	virtual void SetScale( int32_t width, int32_t height ) override;

	virtual void SetCaption( /*In*/ const wchar_t* caption ) override;
	

/*
	Gets
*/
	virtual void GetPosition( /*Out*/ int32_t* x, /*Out*/ int32_t* y ) const override;

	virtual void GetSize( /*Out*/ int32_t* width, /*Out*/ int32_t* height ) const override;

	virtual void GetCaption( /*Out*/ wchar_t* caption ) const override;
	
	HWND GetWindowHandle( ) const;


/*
	Internal works
*/
private:
	void CreateWindowForm( /*In*/ const WindowStyle& );

	void AdditionalInit( /*In*/ const WindowStyle& );

	virtual LRESULT ProcessMessage( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam );


/*
	Private variables
*/
private:
	HWND m_wndHandle;

};


inline HWND tgon::WindowsWindow::GetWindowHandle( ) const
{
	return m_wndHandle;
}

inline void tgon::WindowsWindow::Show( )
{
	ShowWindow( m_wndHandle, SW_NORMAL );
}

inline void tgon::WindowsWindow::Hide( )
{
	ShowWindow( m_wndHandle, SW_HIDE );
}

inline void tgon::WindowsWindow::Maximize( )
{
	ShowWindow( m_wndHandle, SW_MAXIMIZE );
}

inline void tgon::WindowsWindow::Minimize( )
{
	ShowWindow( m_wndHandle, SW_MINIMIZE );
}

inline void tgon::WindowsWindow::Quit( )
{
	PostQuitMessage( 0 );
}

inline void tgon::WindowsWindow::SetPosition(
	int32_t x, int32_t y ) 
{
	SetWindowPos( m_wndHandle, nullptr, x, y, 0, 0, SWP_NOSIZE );
}

inline void tgon::WindowsWindow::SetScale(
	int32_t width,
	int32_t height ) 
{
	SetWindowPos( m_wndHandle, nullptr, 0, 0, width, height, SWP_NOMOVE );
}

inline void tgon::WindowsWindow::SetCaption(
	const wchar_t* caption )
{
	SetWindowTextW( m_wndHandle, caption );
}


}