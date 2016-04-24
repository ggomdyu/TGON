/*
* Author : Junho-Cha
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Abstracted platform API
*/

#pragma once
#include <stdint.h>
#include "../../Core/TNoncopyable.h"


namespace tgon
{


class LayeredApplication : Noncopyable
{
private:
	virtual bool DispatchEvent( 
		enum struct WindowEvent* const ) = 0;

	virtual void GetScreenSize(
		int32_t* width,
		int32_t* height ) = 0;

	virtual struct TSystemBatteryInfo GetPowerInfo( ) = 0;

protected:
	LayeredApplication( ) {};
	virtual ~LayeredApplication( ) = 0 {};
};


}