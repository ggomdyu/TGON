/*
* Author : Cha Junho
* Date : 03/20/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Abstract/AbstractScreen.h"

#include <windows.h>


namespace tgon
{


using ScreenImpl = class WindowsScreen;


class TGON_API WindowsScreen : 
	public AbstractScreen
{
public:
	/*
		Cons/Destructor
	*/
	WindowsScreen( ) = delete;

	virtual ~WindowsScreen( ) = delete;


	/*
		Commands
	*/


	/*
		Sets
	*/


	/*
		Gets
	*/
	// Get monitor's count. Return 0 on Win95/NT.
	static int32_t GetMonitorCount( );

	// Get main monitor's screen width. This function works exactly on single monitor.
	static int32_t GetMainWidth( );

	// Get main monitor's screen height. This function works exactly on single monitor.
	static int32_t GetMainHeight( );
};


}


inline int32_t tgon::WindowsScreen::GetMonitorCount( )
{
	return GetSystemMetrics( SM_CMONITORS );
}

inline int32_t tgon::WindowsScreen::GetMainWidth( )
{
	return GetSystemMetrics( SM_CXSCREEN );
}

inline int32_t tgon::WindowsScreen::GetMainHeight( )
{
	return GetSystemMetrics( SM_CYSCREEN );
}