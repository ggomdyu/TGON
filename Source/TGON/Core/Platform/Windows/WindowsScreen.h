/**
 * @filename    WindowsScreen.h
 * @author      ggomdyu
 * @since       03/20/2016
 */

#pragma once
#include "../Generic/GenericScreen.h"

namespace tgon {
namespace screen {

class TGON_API WindowsScreen : 
	public GenericScreen
{
/** 
 * @section Ctor/Dtor
 */ 
public:
    WindowsScreen() = delete;
    ~WindowsScreen() = delete;

/**
 * @section Public command method
 */
public:	
    static bool SetFullScreen(bool setFullScreen, const class WindowsWindow& window);

	/* @return  The count of monitor. Return 0 on Win95/NT. */
    static int32_t GetMonitorCount();

	/**
	 * @warn    This function works exactly on single monitor!
	 * @return  The width of resolution.
	 */
    static int32_t GetResolutionWidth();

	/**
	 * @warn    This function works exactly on single monitor!
	 * @return  The height of resolution.
	 */
	static int32_t GetResolutionHeight();
};

using Screen = WindowsScreen;

} /* namespace screen */
} /* namespace tgon */