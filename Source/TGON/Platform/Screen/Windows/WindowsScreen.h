/*
* Author : Cha Junho
* Date : 03/20/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Abstract/AbstractScreen.h"


namespace tgon
{


class WindowsScreen;
using ScreenImpl = WindowsScreen;


class TGON_API WindowsScreen : 
	public AbstractScreen
{
/*
	Commands
*/
public:


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

	
/*
	Cons/Destructor
*/
public:
	WindowsScreen( ) = delete;

	virtual ~WindowsScreen( ) = delete;

};


}