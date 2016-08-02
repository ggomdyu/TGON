/*
* Author : Cha Junho
* Date : 03/20/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Abstract/AbstractApplication.h"

#include "../TApplicationType.h"
#include <cassert>


#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	undef WIN32_LEAN_AND_MEAN
#endif

#ifdef RegisterClass
	#undef RegisterClass
#endif


namespace tgon
{


class WindowsWindow;
class WindowsApplication;

using ApplicationImpl = WindowsApplication;


class TGON_API WindowsApplication : 
	public AbstractApplication
{
public:
	static const wchar_t* AppClassName;

public:
	/*
		Cons/Destructor
	*/
	WindowsApplication( );

	virtual ~WindowsApplication( );


	/*
		Commands
	*/
	// Update the event queue. Return false if it's empty.
	virtual bool PumpEvent( ) override;

	virtual void ExitThread( ) override;

	virtual void Quit( int32_t exitCode ) override;


	/*
		Sets
	*/
	void EnableVisualStyles( );


	/*
		Gets
	*/
	virtual TSystemBatteryInfo GetPowerInfo( ) override;

	HINSTANCE GetInstanceHandle( );

	static WindowsWindow* GetWindowFromHWND( HWND wndHandle );


private:
	static LRESULT WINAPI MessageProc( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam );

	bool RegisterClass( );
};


inline void WindowsApplication::EnableVisualStyles( )
{
	assert( false && "EnableVisualStyles function is deprecated." );

	//wchar_t dir[MAX_PATH]{ 0 };
	//ULONG_PTR ulpActivationCookie = FALSE;

	//ACTCTX actCtx =
	//{
	//	sizeof( actCtx ),
	//	ACTCTX_FLAG_RESOURCE_NAME_VALID
	//	| ACTCTX_FLAG_SET_PROCESS_DEFAULT
	//	| ACTCTX_FLAG_ASSEMBLY_DIRECTORY_VALID,
	//	L"shell32.dll", 0, 0, dir, ( LPCWSTR )124
	//};
	//UINT cch = GetSystemDirectory( dir, sizeof( dir ) / sizeof( *dir ) );
	//if ( cch >= sizeof( dir ) / sizeof( *dir ) ) {
	//	int n = 3;
	//	return; /*shouldn't happen*/
	//}
	////dir[cch] = TEXT('\0');
	//HANDLE handle = CreateActCtx( &actCtx );
	//if ( handle == NULL )
	//{
	//	int n = 3;
	//}

	//BOOL isS = ActivateActCtx( handle, &ulpActivationCookie );

	//if ( isS == FALSE )
	//{
	//	auto err = GetLastError( );
	//	int n = 3;
	//}
}

inline void tgon::WindowsApplication::ExitThread( )
{
	::ExitThread( 0 );
}

inline void WindowsApplication::Quit( int32_t exitCode )
{
	PostQuitMessage( exitCode );
}

inline HINSTANCE tgon::WindowsApplication::GetInstanceHandle( )
{
	static HINSTANCE ret = GetModuleHandle( nullptr );
	return ret;
}

inline WindowsWindow* WindowsApplication::GetWindowFromHWND( HWND wndHandle )
{
	return reinterpret_cast<WindowsWindow*>( GetWindowLongPtrW( wndHandle, GWLP_USERDATA ));
}


}