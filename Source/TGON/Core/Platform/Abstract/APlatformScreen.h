/*
* Author : Cha Junho
* Date : 07/05/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../Platform/PlatformInclude.h"

#include <boost/noncopyable.hpp>
#include <cstdint>


namespace tgon
{


class TGON_API AbstractScreen :
	private boost::noncopyable
{
	// 
	// Commands
	// 


	// 
	// Sets
	// 


	// 
	// Gets
	// 
	/* Get monitor's count. */
	static int32_t GetMonitorCount( );

	/* Get main monitor's screen width. */
	static int32_t GetMainWidth( );

	/* note	Get main monitor's screen height. */
	static int32_t GetMainHeight( );
	
	// 
	// Ctor/Dtor
	// 
public:
	AbstractScreen( ) = delete;
	virtual ~AbstractScreen( ) = delete;

};


inline int32_t AbstractScreen::GetMonitorCount( )
{
	return 0;
}

inline int32_t AbstractScreen::GetMainWidth( )
{
	return 0;
}

inline int32_t AbstractScreen::GetMainHeight( )
{
	return 0;
}


}