/*
* 작성자 : 차준호
* 작성일 : 2016-03-20
* 최종 수정 :
* 최종 수정일 :
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

	virtual void GetCursorPosition( int32_t* const x,
									int32_t* const y ) = 0;

	virtual struct TSystemBatteryInfo GetPowerInfo( ) = 0;
};


}