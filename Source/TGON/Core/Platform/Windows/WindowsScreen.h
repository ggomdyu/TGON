/*
* Author : Cha Junho
* Date : 03/20/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Generic/GenericScreen.h"

#include <Windows.h>


namespace tgon
{


class TGON_API WindowsScreen : 
	public GenericScreen<WindowsScreen>
{
public:
	// 
	// Commands
	// 
	/* @return Return monitor's count. Return 0 on Win95/NT. */
	static int32_t GetMonitorCount( );

	/*
	 * @note This function works exactly on single monitor.
	 * @return Return main monitor's screen width.
	*/
	static int32_t GetMainWidth( );

	/*
	 * @note This function works exactly on single monitor.
	 * @return Return main monitor's screen height.
	*/
	static int32_t GetMainHeight( );

public:
	// 
	// Ctor/Dtor
	// 
	WindowsScreen( ) = delete;
	~WindowsScreen( ) = delete;

};


using TPlatformScreen = WindowsScreen;



} /*namespace tgon*/