#pragma once
#include "WindowsWindow.h"

#include "../../Config/Compiler/SyntaxCompatible.hpp"


TGON_FORCEINLINE void tgon::WindowsWindow::Show( ) 
{
	ShowWindow( m_wndHandle, SW_NORMAL );
}

TGON_FORCEINLINE void tgon::WindowsWindow::Hide( )
{
	ShowWindow( m_wndHandle, SW_HIDE );
}

TGON_FORCEINLINE void tgon::WindowsWindow::Maximize( )
{
	ShowWindow( m_wndHandle, SW_MAXIMIZE );
}

TGON_FORCEINLINE void tgon::WindowsWindow::Minimize( )
{
	ShowWindow( m_wndHandle, SW_MINIMIZE );
}

TGON_FORCEINLINE void tgon::WindowsWindow::Quit( )
{
	PostQuitMessage( 0 );
}

TGON_FORCEINLINE void tgon::WindowsWindow::SetPosition(
		const int32_t x,
		const int32_t y ) 
{
	SetWindowPos( m_wndHandle, nullptr, x, y, 0, 0, SWP_NOSIZE );
}

TGON_FORCEINLINE void tgon::WindowsWindow::SetSize(
		const int32_t width,
		const int32_t height ) 
{
	SetWindowPos( m_wndHandle, NULL, 0, 0, width, height, SWP_NOMOVE );
}

TGON_FORCEINLINE bool tgon::WindowsWindow::IsQuitted( ) const
{
	return m_isDestroyed;
}

TGON_FORCEINLINE void tgon::WindowsWindow::SetCaption(
		const wchar_t* const caption )
{
	SetWindowTextW( m_wndHandle, caption );
}