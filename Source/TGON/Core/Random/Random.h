/*
* Author : Cha Junho
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description :
*/

#pragma once
#include "../Platform/OSAL/PlatformInclude.h"


namespace tgon
{


class TGON_API Random
{
	// 
	// Commands
	// 
public:
	/* @return	Return random value between min~max as int */
	static int Range( int min, int max );

	/* @return	Return random value between min~max as float */
	static float Range( float min, float max );

	// 
	// Internal works
	// 
private:
	//
	// @note	WELL Random number generator which faster than the mersenne-Twister above 40%
	// @cf		http://www.iro.umontreal.ca/~panneton/WELLRNG.html
	// @return	Return random value between 0.0~1.0
	//
	static float WELLRNG512a( );

	// 
	// Ctor/Dtor
	// 
private:
	Random( ) = delete;
};


} /*namespace tgon*/