/*
* Author : Cha Junho
* Date : 03/20/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Abstract/APlatformApplication.h"

#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>

#ifdef RegisterClass
	#undef RegisterClass
#endif


namespace tgon
{


class TGON_API WindowsPlatformApplication :
	public APlatformApplication
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
	virtual bool PumpEvent( ) override;

	/*
	 * @note Exit thread by force. This function is not recommended.
	 * @param exitCode Pass exit code.
	*/
	virtual void ExitThread( int32_t exitCode ) override;

	/*
	 * @note Quit application with passing exit code.
	 * @param exitCode Pass exit code.
	*/
	virtual void Quit( int32_t exitCode ) override;

	/*
	 * @note Toggle the full-screen.
	 * @return Return true on success.
	*/
	virtual bool ToggleFullScreen( const class APlatformWindowFrame& window ) override;

	/*
	 * @note Enable show cursor mode: Hide or Show
	 * @param enableShow True is show, false is hide.
	*/
	virtual void ShowCursor( bool enableShow );


	//
	// Sets
	//


	// 
	// Gets
	//
	static WindowsPlatformApplication& Get( )
	{
		static WindowsPlatformApplication instance;
		return instance;
	}

	/*
	 * @note Get the system power information. Desktop does not apply.
	 * @return Return the property that described about system power.
	*/
	virtual BatteryProperty GetPowerInfo( ) const override;

	/*
	 * @return Return the program application's instance handle.
	*/


	// 
	// Ctor/Dtor
	// 
public:
	WindowsPlatformApplication( );
	virtual ~WindowsPlatformApplication( ) = default;


	// 
	// Internal works
	// 
private:
	/* @note Static message procedure */
	static LRESULT WINAPI MessageProc( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam );

	/* @note Register default WNDCLASSEX */
	bool RegisterDefWndClass( );
};

using TApplication = WindowsPlatformApplication;


} /*namespace tgon*/