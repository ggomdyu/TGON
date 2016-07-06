/*
* Author : Cha Junho
* Date : 07/05/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../../Platform/Config/Build.h"


namespace tgon
{


class TGON_API AbstractScreen :
	private boost::noncopyable
{
public:
	/*
		Cons/Destructor
	*/
	AbstractScreen( ) = delete;
	
	virtual ~AbstractScreen( ) = delete;


	/*
		Commands
	*/


	/*
		Sets
	*/


	/*
		Gets
	*/
	// Get monitor's count.
	static int32_t GetMonitorCount( ) {};

	// Get main monitor's screen width.
	static int32_t GetMainWidth( ) {}

	// Get main monitor's screen height.
	static int32_t GetMainHeight( ) {}
};


}