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

protected:
	/*
		Cons/Destructor
	*/
	explicit WindowsWindow( const WindowStyle& );

	virtual ~WindowsWindow( );

public:
	/*
		Commands
	*/
	virtual bool PumpEvent( ) override;

	virtual void Show( ) override;

	virtual void Hide( ) override;

	virtual void Quit( ) override;

	virtual void Maximize( ) override;

	virtual void Minimize( ) override;

	virtual void BringToTop( ) override;

	virtual void Flash( ) override;

	virtual void EnableGlobalMouseFocus( bool isEnable );


	/*
		Sets
	*/
	virtual void SetPosition( int32_t x, int32_t y ) override;

	virtual void SetScale( int32_t width, int32_t height ) override;

	virtual void SetCaption( IN const wchar_t* caption );
	

	/*
		Gets
	*/
	virtual void GetPosition( OUT int32_t* x, OUT int32_t* y ) const override;

	virtual void GetSize( OUT int32_t* width, OUT int32_t* height ) const override;

	virtual void GetCaption( OUT wchar_t* caption ) const override;
	
	HWND GetWindowHandle( ) const;


private:
	/*
		Internal works
	*/
	void CreateWindowForm( IN const WindowStyle& );

	void AdditionalInit( IN const WindowStyle& );

	virtual LRESULT ProcessMessage( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam );


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