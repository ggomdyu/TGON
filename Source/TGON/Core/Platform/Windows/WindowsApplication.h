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
public:
	/*
	 * @note	Update all of message queue.
	 * @return	Return false if there is no event to pump out
	*/
	static bool PumpEvent( );

	/*
	 * @note	Exit thread by force. This function is not recommended.
	 * @param	exitCode Pass exit code.
	*/
	static void ExitThread( int32_t exitCode );

	/*
	 * @note				Quit application with passing exit code.
	 * @param	exitCode	Pass exit code.
	*/
	static void Quit( int32_t exitCode );

	/*
	 * @note				Enable show cursor mode: Hide or Show
	 * @param	enableShow	Pass true to show, false otherwise.
	*/
	static void ShowCursor( bool enableShow );

	/**/
	//static void DisableTaskSwitching( );

	//
	// Event handler
	//
public:
	/* @note	Message procedure */
	static LRESULT WINAPI OnMessageHandled( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam );

	// 
	// Ctor/Dtor
	// 
public:
	WindowsApplication( ) = delete;
	~WindowsApplication( ) = delete;

};

using TApplication = WindowsApplication;


} /*namespace tgon*/