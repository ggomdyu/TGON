/*
* Author : Cha Junho
* Date : 03/20/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Abstract/AbstractApplication.h"

#include "../TApplicationType.h"
#include <Windows.h>
#ifdef RegisterClass
	#undef RegisterClass
#endif


namespace tgon
{


class WindowsApplication;

using ApplicationImpl = WindowsApplication;


class TGON_API WindowsApplication : 
	public AbstractApplication
{
public:
	static const wchar_t* AppClassName;


/*
	Commands
*/
	//
	// Update the event queue. Return false if it's empty.
	//
	// @return Return false on idle time. 
	//
	virtual bool PumpEvent( ) override;

	//
	// Exit thread by force. This function is not recommended on quit.
	//
	virtual void ExitThread( int32_t exitCode ) override;

	//
	// Quit the application by passing quit message.
	//
	// @param exitCode
	//
	virtual void Quit( int32_t exitCode ) override;

	//
	// Toggle the full-screen.
	//
	// @return Return true on success.
	//
	virtual bool ToggleFullScreen( const AbstractWindow& ) override;

	//
	// Enable show cursor mode.
	//
	// @param enableShow
	//
	virtual void ShowCursor( bool enableShow );

/*
	Sets
*/
	//
	// TODO : ENABLE THIS
	//
	void EnableVisualStyles( );


/*
	Gets
*/
	virtual TBatteryInfo GetPowerInfo( ) override;


	//
	// Get the program application's instance handle.
	//
	// @platform Windows
	// @param exitCode
	//
	HINSTANCE GetInstanceHandle( );


/*
	Cons/Destructor
*/
public:
	//
	// Constructor
	//
	WindowsApplication( );

	//
	// Destructor
	//
	virtual ~WindowsApplication( );


/*
	Internal works
*/
private:
	static LRESULT WINAPI MessageProc( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam );

	bool RegisterClass( );
};


inline void WindowsApplication::EnableVisualStyles( )
{
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

inline void WindowsApplication::ExitThread( int32_t exitCode )
{
	::ExitThread( exitCode );
}

inline void WindowsApplication::Quit( int32_t exitCode )
{
	PostQuitMessage( exitCode );
}

inline HINSTANCE WindowsApplication::GetInstanceHandle( )
{
	static HINSTANCE ret = GetModuleHandle( nullptr );
	return ret;
}

inline void WindowsApplication::ShowCursor( bool enableShow )
{
	::ShowCursor(( enableShow ) ? TRUE : FALSE );
}


}