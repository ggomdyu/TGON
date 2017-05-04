/*
 * @author   ggomdyu
 * since    03/20/2016


*/


#pragma once
#include "../Generic/GenericSystem.h"


namespace tgon
{


class TGON_API WindowsSystem :
	public GenericSystem<WindowsSystem>
{
	/* 
	 * Ctor/Dtor
	*/ 
public:
	WindowsSystem( ) = delete;
	~WindowsSystem( ) = delete;

	/*
	 * Commands
	*/
public:
	static BatteryProperty GetPowerInfo( );	
};


using System = WindowsSystem;


} /* namespace tgon */
