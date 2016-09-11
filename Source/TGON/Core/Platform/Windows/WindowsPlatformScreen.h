/*
* Author : Cha Junho
* Date : 03/20/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Abstract/APlatformScreen.h"

#include <Windows.h>


namespace tgon
{


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
	//
	// @return Return monitor's count. Return 0 on Win95/NT.
	//
	static int32_t GetMonitorCount( );

	//
	// @note This function works exactly on single monitor.
	// @return Return main monitor's screen width.
	//
	static int32_t GetMainWidth( );

	//
	// @note This function works exactly on single monitor.
	// @return Return main monitor's screen height.
	//
	static int32_t GetMainHeight( );


	/*
		Ctor/Dtor
	*/
public:
	WindowsScreen( ) = delete;

	virtual ~WindowsScreen( ) = delete;

};


using TPlatformScreen = WindowsScreen;



} /*namespace tgon*/