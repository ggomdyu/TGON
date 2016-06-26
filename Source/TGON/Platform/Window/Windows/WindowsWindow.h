/*
* Author : Junho-Cha
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
#endif WIN32_LEAN_AND_MEAN


#include <string> // TEST


namespace tgon
{


using WindowImpl = class WindowsWindow;


class TGON_API WindowsWindow : 
	public AbstractWindow
{
protected:
	explicit WindowsWindow( const struct WindowStyle& );

	virtual ~WindowsWindow( );

public:
	/*
		Commands
	*/
	virtual void Show( ) override;

	virtual void Hide( ) override;

	virtual void Quit( ) override;

	virtual void Maximize( ) override;

	virtual void Minimize( ) override;

	virtual void BringToTop( ) override;

	void Flash( );


	/*
		Sets
	*/
	virtual void SetPosition( int32_t x, int32_t y ) override;

	virtual void SetScale( int32_t width, int32_t height ) override;

	virtual void SetCaption( _In_ const wchar_t* caption );
	

	/*
		Gets
	*/
	virtual void GetPosition( _Out_ int32_t* x, _Out_ int32_t* y ) const override;

	virtual void GetSize( _Out_ int32_t* width, _Out_ int32_t* height ) const override;

	virtual void GetCaption( _Out_ wchar_t* caption ) const override;
	
	virtual bool IsDestroyed( ) const;

	HWND GetWindowHandle( ) const;


private:
	void CreateWindowForm( _In_ const struct WindowStyle&, bool isEventHandleable );

	void AdditionalInit( _In_ const struct WindowStyle& );

	bool RegisterMyClass( _In_ const struct WindowStyle& wndStyle, _Out_ std::wstring* outClassName, bool isEventHandleable );
	
	static LRESULT WINAPI UnevHandleMsgProc( HWND, UINT, WPARAM, LPARAM );

	static LRESULT WINAPI EvHandleMsgProc( HWND, UINT, WPARAM, LPARAM );

private:
	bool m_isDestroyed;
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

inline bool tgon::WindowsWindow::IsDestroyed( ) const
{
	return m_isDestroyed;
}

inline void tgon::WindowsWindow::SetCaption(
	const wchar_t* caption )
{
	SetWindowTextW( m_wndHandle, caption );
}


}