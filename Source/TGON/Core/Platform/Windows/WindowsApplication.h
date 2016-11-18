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
	/* 
	 * Ctor/Dtor
	*/ 
public:
	WindowsApplication( ) = delete;
	~WindowsApplication( ) = delete;

	/**
	 * Commands
	 */
public:
	/**
	 * @note			Update windows' message queue.
	 * @return			False if there is no event to pull out
	 */
	static bool PumpEvent( );
	
	/**
	 * @note			Post quit message to its queue.
	 * @param	exitCode	Exit code
	 */
	static void Quit( int32_t exitCode );

	/**
	 * @note			Terminate thread by force. Not recommended.
	 * @param	exitCode	Exit code
	 */
	static void ExitThread( int32_t exitCode );

	/**
	 * @note			Enable show cursor mode: Hide or Show
	 * @param	enableShow	Pass true to show, false otherwise.
	 */
	static void ShowCursor( bool enableShow );

	/**
	 * @note			Enable float calculate exception like: devide by zero, underflow, overflow, etc 
	 */
	static void EnableFloatingException( unsigned int newStat );

	/**/
	//static void DisableTaskSwitching( );

	/**
	 * Event handlers
	 */
public:
	/* @note	Message procedure */
	static LRESULT WINAPI OnMessageHandled( HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam );

	/**
	 * Variables
	 */
public:
	static const HINSTANCE InstanceHandle;
	static const wchar_t* AppClassName;
};


using Application = WindowsApplication;


} /*namespace tgon*/
