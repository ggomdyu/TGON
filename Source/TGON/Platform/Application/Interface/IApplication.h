/*
* Author : Junho-Cha
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Platform abstraction API
*/


#pragma once
#include <stdint.h>
#include "../TApplicationType.h"
#include "../../../Platform/Config/Build.h"
#include <Window/WindowEvent.h>

namespace tgon
{


class TGON_API IApplication
{
public:
	static bool DispatchEvent( WindowEvent* ) {}
	static void GetScreenSize( int32_t* width, int32_t* height ) {}
	static TSystemBatteryInfo GetPowerInfo( ) {}

private:
	IApplication( ) = delete;
	~IApplication( ) = delete;
};


}