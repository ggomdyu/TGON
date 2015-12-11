/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� : 
* ���� ������ :
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

	public:
		virtual void					Show( ) override;
		virtual void					BringToTop( ) override;
		virtual void					SetPosition( const int x, const int y ) override;
		virtual void					Move( const int x, const int y ) override;
		virtual void					Exit( ) override;

	public:
		virtual bool					PumpWindowEvent( ) override;
		HWND						GetWindowHandle( ) const;

	private:
		virtual void					MakeWindow( _In_ const WindowStyle& ws ) override;

		static LRESULT WINAPI		CallbackMsgProc( HWND, uint32_t, WPARAM, LPARAM );
		virtual LRESULT WINAPI	CustomMsgProc( HWND, uint32_t, WPARAM, LPARAM );	/* can override! */
		 
	private:
		HWND			m_wndHandle;
	};
}