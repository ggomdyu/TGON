/*
 * Author : Cha Junho
 * Date : 03/20/2016
 * Latest author :
 * Latest date :
*/


#pragma once
#include "../OSAL/PlatformInclude.h"

#include <cstdint>
#include <boost/noncopyable.hpp>


namespace tgon 
{


struct BatteryProperty
{
	bool hasBattery;
	uint16_t batteryLifePercent; // 0% ~ 100%
};

//template <typename Deri
class TGON_API APlatformApplication :
	private boost::noncopyable
{
	// 
	// Commands
	// 
public:
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
	static bool ToggleFullScreen( const class APlatformWindow& );

	/*
	 * @note Enable show cursor mode: Hide or Show
	 * @param enableShow True is show, false is hide.
	*/
	static void ShowCursor( bool enableShow );

	// 
	// Gets
	// 
	/*
	 * @note Get the system power information. Desktop does not apply.
	 * @return Return the property that described about system power.
	*/
	static BatteryProperty GetPowerInfo( );

	// 
	// Ctor/Dtor
	// 
public:
	APlatformApplication( ) = delete;
	virtual ~APlatformApplication( ) = delete;

};


} /*namespace tgon*/


#include "APlatformApplication.inl"