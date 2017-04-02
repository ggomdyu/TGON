/*
 * author   ggomdyu
 * since    03/20/2016


*/


#pragma once
#include "../Generic/GenericScreen.h"


namespace tgon
{


class TGON_API WindowsScreen : 
	public GenericScreen<WindowsScreen>
{
	/* 
	 * Ctor/Dtor
	*/ 
public:
	WindowsScreen( ) = delete;
	~WindowsScreen( ) = delete;

	/* 
	 * Commands
	*/ 
public:	
	/*
	 * @note	Toggle the full-screen.
	 * @return	Return true on success.
	*/
	static bool ToggleFullScreen( const class GenericWindowFrame& window );

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
};


using Screen = WindowsScreen;


} /* namespace tgon */
