/*
* Author : Junho-Cha
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Abstract-API Sets for Windows
*/


#pragma once
#include "../../Window/TWindow.h"
#include "../Platform/Config/Build.h"


namespace tgon
{


class TGON_API AbstractApplication
{
public:
	static int32_t Run( const SpTWindow& );
	static void ExitThread( );
	static void Exit( int32_t exitCode );
	static void Quit( int32_t exitCode );
	static void Restart( );
	static void GetScreenSize( int32_t* width, int32_t* height );

private:
	static void SubMessageProc( const SpTWindow&, const SDL_Event& );

private:
	AbstractApplication( ) = delete;
	virtual ~AbstractApplication( ) = delete;
};

inline void AbstractApplication::Quit( 
	int32_t exitCode )
{
	SDL_Quit( );
}

inline void AbstractApplication::GetScreenSize(
	int32_t* width, 
	int32_t* height )
{
	SDL_DisplayMode displayMode;
	if ( SDL_GetCurrentDisplayMode( 0, &displayMode ) < 0 )
	{
		// TODO : Log here
	}

	*width = displayMode.w;
	*height = displayMode.h;
}


}