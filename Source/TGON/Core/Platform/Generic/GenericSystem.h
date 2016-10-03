/*
 * Author : Cha Junho
 * Date : 03/20/2016
 * Latest author :
 * Latest date :
*/


#pragma once
#include "../PlatformInclude.h"

#include <cstdint>


namespace tgon 
{


struct BatteryProperty
{
	BatteryProperty( bool _hasBattery, uint16_t _batteryLifePercent ) noexcept :
		hasBattery( _hasBattery ),
		batteryLifePercent( _batteryLifePercent )
	{
	}

	const bool hasBattery;
	const uint16_t batteryLifePercent; // 0% ~ 100%
};

template <typename DerivedTy>
class TGON_API GenericSystem
{
	// 
	// Gets
	//
public:
	/*
	 * @note Get the system power information. Desktop does not apply.
	 * @return Return the property that described about system power.
	*/
	static BatteryProperty GetPowerInfo( ) { return BatteryProperty{ false, 0 }; }

	// 
	// Ctor/Dtor
	// 
public:
	GenericSystem( ) = delete;
	~GenericSystem( ) = delete;

};


} /*namespace tgon*/
