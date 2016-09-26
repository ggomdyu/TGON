/*
* Author : Cha Junho
* Date : 03/20/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Generic/GenericApplication.h"

#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>

#ifdef RegisterClass
	#undef RegisterClass
#endif


namespace tgon
{


class TGON_API WindowsApplication :
	public GenericApplication<WindowsApplication>
{
	// 
	// Static variables
	// 
public:
	static const HINSTANCE InstanceHandle;
	static const wchar_t* AppClassName;

	// 
	// Commands
	// 
	/*
	 * @note Update all of message queue.
	 * @return Return false if there is no event to pump out
	*/
	static bool PumpEvent( );

	/*
	 * @note Exit thread by force. This function is not recommended.
	 * @param exitCode Pass exit code.
	*/
	static void ExitThread( int32_t exitCode );

	/*
	 * @note Quit application with passing exit code.
	 * @param exitCode Pass exit code.
	*/
	static void Quit( int32_t exitCode );

	/*
	 * @note Toggle the full-screen.
	 * @return Return true on success.
	*/
	static bool ToggleFullScreen( const class GenericWindowFrame& window );

	/*
	 * @note Enable show cursor mode: Hide or Show
	 * @param enableShow True is show, false is hide.
	*/
	static void ShowCursor( bool enableShow );


	//
	// Event handler
	//
	static LRESULT WINAPI OnMessageHandled( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam );
	
	
	//
	// Sets
	//
	/*
	 * @note Get the system power information. Desktop does not apply.
	 * @return Return the property that described about system power.
	*/
	static BatteryProperty GetPowerInfo( );

	/*
	 * @return Return the program application's instance handle.
	*/

	// 
	// Ctor/Dtor
	// 
public:
	WindowsApplication( ) = delete;
	virtual ~WindowsApplication( ) = delete;


	// 
	// Internal works
	// 
private:
	/* @note Static message procedure */

};

using TApplication = WindowsApplication;


} /*namespace tgon*/