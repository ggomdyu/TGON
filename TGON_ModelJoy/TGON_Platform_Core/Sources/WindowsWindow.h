/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� : 
* ���� ������ :
*/

#pragma once
#include "GenericWindow.h"

#define WIN32_LEAN_AND_MEAN /* fwd declare */
#include <Windows.h>


namespace tgon {
	class WindowsWindow;
	typedef WindowsWindow Window;

	class WindowsWindow final : public GenericWindow
	{
	public:
		explicit WindowsWindow( _In_ const WindowStyle& );
		virtual ~WindowsWindow( );

		virtual void FrameMove( ) override;
		
	public:
		virtual void Show( ) override;
		virtual void BringToTop( ) override;
		virtual void SetPosition( const int x, const int y ) override;
		virtual void Move( const int x, const int y ) override;
		virtual void Exit( ) override;

		virtual const WindowEvent GetWindowEvent( ) const override;
		HWND GetWindowHandle( ) const;

	private:
		void MakeWindow( _In_ const WindowStyle& );

		static LRESULT WINAPI CallbackMsgProc( HWND, uint32_t, WPARAM, LPARAM );
		virtual LRESULT WINAPI CustomMsgProc( HWND, uint32_t, WPARAM, LPARAM );	/* can override! */
		 
	private:
		MSG msg;
		HWND m_wndHandle;
	};
}