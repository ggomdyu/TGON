/*
* Author : Cha Junho
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : API Sets for Windows
*/


#pragma once
#include "../Abstract/AbstractApplication.h"
#include "../TApplicationType.h"


#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#	include <Windows.h>
#	undef WIN32_LEAN_AND_MEAN
#endif


namespace tgon
{


using ApplicationImpl = class WindowsApplication;


class TGON_API WindowsApplication : 
	public AbstractApplication
{
public:
	/*
		Cons/Destructor
	*/
	WindowsApplication( ) = delete;

	virtual ~WindowsApplication( ) = delete;


	/*
		Commands
	*/
	static int32_t Run( _In_ class WindowsWindow& );

	static void ExitThread( );

	static void Quit( int32_t exitCode );

	static void EnableVisualStyles( );


	/*
		Sets
	*/


	/*
		Gets
	*/
	static void GetScreenSize( _Out_ int32_t* width, _Out_ int32_t* height );

	static TSystemBatteryInfo GetPowerInfo( );

	static HINSTANCE GetInstanceHandle( );
};

inline void WindowsApplication::GetScreenSize( int32_t* width, int32_t* height )
{
	*width = GetSystemMetrics( SM_CXSCREEN );
	*height = GetSystemMetrics( SM_CYSCREEN );
}

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
	static HINSTANCE instanceHandle = GetModuleHandle( nullptr );
	return instanceHandle;
}


}