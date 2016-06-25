/*
* Author : Junho-Cha
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Abstract-API Sets for Windows
*/


#pragma once
#include "../../Slate/PlatformFwd.h"
#include "../../Config/Build.h"


namespace tgon
{


class TGON_API AbstractApplication
{
public:
	static int32_t Run( 
		/*IN*/ const SpTWindow& );

	static void Quit( 
		/*IN*/ int32_t exitCode );

	static void GetScreenSize( 
		/*OUT*/ int32_t* width, 
		/*OUT*/ int32_t* height );

private:
	static void SubMessageProc( 
		/*IN*/ const SpTWindow&, 
		/*IN*/ const SDL_Event& );

private:
	AbstractApplication( ) = delete;
	virtual ~AbstractApplication( ) = delete;
	
};

inline void AbstractApplication::Quit( 
	int32_t exitCode )
{
	SDL_Quit( );
}


}