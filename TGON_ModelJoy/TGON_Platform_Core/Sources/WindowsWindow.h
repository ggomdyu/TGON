/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 : 
* 최종 수정일 :
*/

#pragma once
#ifndef TGON_USE_PRECOMPILED_HEADER
	#define WIN32_LEAN_AND_MEAN /* fwd declare */
	#include <Windows.h>
#endif

#include "GenericWindow.h"

namespace tgon {
	class WindowsWindow;
	typedef WindowsWindow Window;

	class WindowsWindow final : public GenericWindow
	{
	public:
		explicit						WindowsWindow( _In_ const WindowStyle& );
		virtual							~WindowsWindow( );

		virtual bool					PumpWindowEvent( ) override;

	public:
		virtual void					Show( ) override;
		virtual void					BringToTop( ) override;
		virtual void					SetPosition( const int x, const int y ) override;
		virtual void					Move( const int x, const int y ) override;
		virtual void					Exit( ) override;

		HWND						GetWindowHandle( ) const;

	private:
		void							MakeWindow( _In_ const WindowStyle& );

		static LRESULT WINAPI	CallbackMsgProc( HWND, uint32_t, WPARAM, LPARAM );
		virtual LRESULT WINAPI	CustomMsgProc( HWND, uint32_t, WPARAM, LPARAM );	/* can override! */
		 
	private:
		HWND						m_wndHandle;
	};
}