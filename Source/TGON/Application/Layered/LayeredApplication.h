/*
* Author : Junho-Cha
* Date : 2016-03-20
* Latest author :
* Latest date :
* Description : Abstracted platform API & Util
*/

#pragma once
#include "../../Window/TWindow.h"
#include <map>
#include <stdint.h>


namespace tgon
{


class LayeredApplication
{
protected:
	LayeredApplication( ) {};
	virtual ~LayeredApplication( ) = 0 {};

private:
	virtual void DispatchEvent( _Out_ enum struct WindowEvent* const ) = 0;

	virtual void GetScreenSize( int32_t* const width,
								int32_t* const height ) = 0;

	virtual struct TSystemBatteryInfo GetPowerInfo( ) = 0;
};


}