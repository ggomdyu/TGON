/*
* Author : Junho-Cha
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Platform abstraction API
*/

#pragma once
#include <stdint.h>
#include "../../Core/TObject.h"
#include "../../Core/TNoncopyable.h"


namespace tgon
{


class TGON_API IApplication : 
	public TObject,
	private TNoncopyable
{
public:
	TGON_OBJECT( IApplication, TObject )

public:
	virtual bool DispatchEvent( enum struct WindowEvent* ) = 0;
	virtual void GetScreenSize( int32_t* width, int32_t* height ) = 0;
	virtual struct TSystemBatteryInfo GetPowerInfo( ) = 0;

protected:
	IApplication( ) {};
	virtual ~IApplication( ) = 0 {};
};


}