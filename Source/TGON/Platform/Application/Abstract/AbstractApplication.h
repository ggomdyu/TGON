/*
* Author : Cha Junho
* Date : 03/20/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../../Platform/Config/Build.h"

#include "../TApplicationType.h"


namespace tgon
{


class TWindow;

class TGON_API AbstractApplication
{
public:
	/*
		Cons/Destructor
	*/
	AbstractApplication( ) = default;
	
	virtual ~AbstractApplication( ) = default;


	/*
		Commands
	*/
	//Update the event queue. Return false if the system queue is empty.
	virtual bool PumpEvent( ) = 0;

	virtual void ExitThread( ) = 0;

	virtual void Quit( int32_t exitCode ) = 0;


	/*
		Gets
	*/
	virtual struct TSystemBatteryInfo GetPowerInfo( ) = 0;

};


}