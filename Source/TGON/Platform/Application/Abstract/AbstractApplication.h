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


class AbstractWindow;

class TGON_API AbstractApplication
{
/*
	Commands
*/
public:
	//
	// Update the event queue. Return false if it's empty.
	//
	// @return Return false on idle time. 
	//
	virtual bool PumpEvent( ) = 0;

	//
	// Exit thread by force. This function is not recommended on quit.
	//
	virtual void ExitThread( int32_t exitCode ) = 0;

	//
	// Quit application with passing exit code.
	//
	// @param exitCode
	//
	virtual void Quit( int32_t exitCode ) = 0;

	//
	// Toggle the full-screen.
	//
	// @return Return true on success.
	//
	virtual bool ToggleFullScreen( const AbstractWindow& );

	//
	// Enable show cursor mode.
	//
	// @param enableShow
	//
	virtual void ShowCursor( bool enableShow );

/*
	Gets
*/
	virtual TBatteryInfo GetPowerInfo( ) = 0;

public:
/*
	Cons/Destructor
*/
	//
	// Constructor
	//
	AbstractApplication( ) = default;
	
	//
	// Destructor
	//
	virtual ~AbstractApplication( ) = default;

};


inline bool tgon::AbstractApplication::ToggleFullScreen( const AbstractWindow & )
{
	return false;
}

inline void AbstractApplication::ShowCursor( bool enableShow )
{
}


}