/*
* Author : Junho-Cha
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Abstract-API Sets for Windows
*/


#pragma once
#include "../Interface/IApplication.h"

#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN


namespace tgon
{


using ApplicationImpl = class WindowsApplication;

class TGON_API WindowsApplication : 
	public IApplication
{
public:
	static bool DispatchEvent( _Out_ enum struct WindowEvent* );
	static void GetScreenSize( int32_t* width, int32_t* height );
	static struct TSystemBatteryInfo GetPowerInfo( );

	static HINSTANCE GetInstanceHandle( );

private:
	WindowsApplication( ) = delete;
	~WindowsApplication( ) = delete;

private:
	static MSG m_msg;
	static const HINSTANCE m_instanceHandle;
};

inline bool tgon::WindowsApplication::DispatchEvent(
	_Out_ WindowEvent* outEvent )
{
	BOOL doesMsgExist = PeekMessageW( &m_msg, nullptr, 0, 0, PM_REMOVE );
	if ( doesMsgExist )
	{
		::TranslateMessage( &m_msg ); // Process WM_CHAR
		::DispatchMessageW( &m_msg );

		*outEvent = static_cast<WindowEvent>( m_msg.message );
		return true;
	}
	else
	{
		*outEvent = WindowEvent::kNone;
		return false;
	}
}

inline HINSTANCE WindowsApplication::GetInstanceHandle( )
{
	return m_instanceHandle;
}

inline void WindowsApplication::GetScreenSize(
	int32_t* width, 
	int32_t* height )
{
	*width = GetSystemMetrics( SM_CXSCREEN );
	*height = GetSystemMetrics( SM_CYSCREEN );
}


}