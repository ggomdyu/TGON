/*
* Author : Junho-Cha
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Abstract-API Sets for Windows
*/


#pragma once
#include "../Abstract/AbstractApplication.h"
#include "../../Window/WindowEvent.h"

#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN


namespace tgon
{


class TGON_API WindowsApplication : 
	public AbstractApplication
{
public:
	static TGON_API const HINSTANCE InstanceHandle;

public:
	/*
		About using window
	*/
	static void Run( class WindowsWindow& );
	static bool MessageLoop( );
	
	/*
		About System
	*/
	static struct TSystemBatteryInfo GetPowerInfo( );
	static void ExitThread( );
	static void Exit( int32_t exitCode );
	static void Quit( int32_t exitCode );
	static void Restart( );

	/*
		About UI
	*/
	static void GetScreenSize( int32_t* width, int32_t* height );
	static void EnableVisualStyles( );



private:
	WindowsApplication( ) = delete;
	~WindowsApplication( ) = delete;

private:
	static TGON_API MSG m_msg;
};

using ApplicationImpl = WindowsApplication;

inline void WindowsApplication::GetScreenSize(
	int32_t* width, 
	int32_t* height )
{
	*width = GetSystemMetrics( SM_CXSCREEN );
	*height = GetSystemMetrics( SM_CYSCREEN );
}

inline void WindowsApplication::EnableVisualStyles( )
{
	wchar_t dir[MAX_PATH]{ 0 };
	ULONG_PTR ulpActivationCookie = FALSE;

	ACTCTX actCtx =
	{
		sizeof( actCtx ),
		ACTCTX_FLAG_RESOURCE_NAME_VALID
		| ACTCTX_FLAG_SET_PROCESS_DEFAULT
		| ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID,
		L"shell32.dll", 0, 0, dir, ( LPCWSTR )124
	};
	UINT cch = GetSystemDirectory( dir, sizeof( dir ) / sizeof( *dir ) );
	if ( cch >= sizeof( dir ) / sizeof( *dir ) ) {
		int n = 3;
		return; /*shouldn't happen*/
	}
	//dir[cch] = TEXT('\0');
	HANDLE handle = CreateActCtx( &actCtx );
	if ( handle == NULL )
	{
		int n = 3;
	}

	BOOL isS = ActivateActCtx( handle, &ulpActivationCookie );

	if ( isS == FALSE )
	{
		auto err = GetLastError( );
		int n = 3;
	}
}

inline void tgon::WindowsApplication::ExitThread( )
{
	::ExitThread( 0 );
}

inline void tgon::WindowsApplication::Exit( int32_t exitCode )
{
	::exit( exitCode );
}

inline void WindowsApplication::Quit( int32_t exitCode )
{
	PostQuitMessage( exitCode );
}

inline void WindowsApplication::Restart( )
{
}



}