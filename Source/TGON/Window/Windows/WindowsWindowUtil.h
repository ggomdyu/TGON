/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


namespace tgon
{
	void convert_wndstyle_to_dword( const struct WindowStyle&,
						_Out_ DWORD* const exWndStyle,
						_Out_ DWORD* const normalWndStyle );

	bool RegisterClass( const struct WindowStyle& wndStyle,
						const WNDPROC wndProc,
						_In_opt_ HICON iconHandle = LoadIcon( NULL, IDI_APPLICATION ));

	void ReshapeWindowFrom( _Out_ const class WindowsWindow* const from,
							const class WindowsWindow* const to );
}