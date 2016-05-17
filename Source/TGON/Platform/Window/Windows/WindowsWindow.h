/*
* Author : Junho-Cha
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once
#include "../Interface/IWindow.h"
#include "../WindowStyle.h"
#include "../WindowEvent.h"

#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#include <stdint.h>
#include <functional>


namespace tgon
{


class WindowsWindow;
using WindowImpl = WindowsWindow;

class TGON_API WindowsWindow : public IWindow
{
public:
	/*
		@ Commands
	*/
	virtual void SetPosition( int32_t x,
				 			  int32_t y ) override;
	virtual void SetScale( int32_t width,
						   int32_t height ) override;
	virtual void SetCaption( const wchar_t* caption );
	virtual void Show( ) override;
	virtual void Hide( ) override;
	virtual void Quit( ) override;
	virtual void Maximize( ) override;
	virtual void Minimize( ) override;
	virtual void BringToTop( ) override;
	virtual void Flash( ) override;
				 
	virtual void GetPosition( _Out_ int32_t* x,
				 			  _Out_ int32_t* y ) const override;
	virtual void GetSize( _Out_ int32_t* width,
						  _Out_ int32_t* height ) const override;
	virtual std::wstring GetCaption( ) const override;
	virtual bool IsDestroyed( ) const;

	HWND GetWindowHandle( ) const;


	/*
		@ Cons/Destructors
	*/
protected:
	explicit WindowsWindow( const struct WindowStyle& );
	virtual ~WindowsWindow( );

	/*
		@ Internal works
	*/
protected:
	virtual void LazyInitialization( ) override;

private:
	void CreateWindowForm( const struct WindowStyle& );
	void AdditionalInit( const struct WindowStyle& );
		 
	bool RegisterMyClass( const WindowStyle& wndStyle,
									 _Out_ std::wstring* outClassName );

	static LRESULT WINAPI UneventableMsgProc( HWND, UINT, WPARAM, LPARAM );
	static LRESULT WINAPI EventableMsgProc( HWND, UINT, WPARAM, LPARAM );


	/*
		@ Private data area
	*/
private:
	WindowStyle m_wndStyle;
	HWND m_wndHandle;
	bool m_isDestroyed;

	std::function<int32_t( class TWindow*, WindowEvent )> m_msgCallback;
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
	SetWindowPos( m_wndHandle, NULL, 0, 0, width, height, SWP_NOMOVE );
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