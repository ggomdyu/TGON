/*
 * Author : Cha Junho
 * Date : 03/20/2016
 * Latest author :
 * Latest date :
*/


#pragma once
#include "../PlatformInclude.h"

#include <cstdint>
#include <boost/noncopyable.hpp>


namespace tgon 
{


struct BatteryProperty
{
	bool hasBattery;
	uint16_t batteryLifePercent; // 0% ~ 100%
};

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
	virtual bool PumpEvent( ) = 0;

	/*
	 * @note Exit thread by force. This function is not recommended.
	 * @param exitCode Pass exit code.
	*/
	virtual void ExitThread( int32_t exitCode ) = 0;

	/*
	 * @note Quit application with passing exit code.
	 * @param exitCode Pass exit code.
	*/
	virtual void Quit( int32_t exitCode ) = 0;

	/*
	 * @note Toggle the full-screen.
	 * @return Return true on success.
	*/
	virtual bool ToggleFullScreen( const class APlatformWindowFrame& ) { return false; }

	/*
	 * @note Enable show cursor mode: Hide or Show
	 * @param enableShow True is show, false is hide.
	*/
	virtual void ShowCursor( bool enableShow ) {};

	// 
	// Gets
	// 
	/*
	 * @note Get the system power information. Desktop does not apply.
	 * @return Return the property that described about system power.
	*/
	virtual BatteryProperty GetPowerInfo( ) const = 0;

	// 
	// Ctor/Dtor
	// 
public:
	APlatformApplication( ) = default;
	virtual ~APlatformApplication( ) = default;

};


} /*namespace tgon*/
