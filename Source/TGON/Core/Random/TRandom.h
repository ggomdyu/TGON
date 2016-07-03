/*
* Author : Cha Junho
* Date : 03/14/2016
* Latest author :
* Latest date :
* Description :
*/

#pragma once
#include "../../Platform/Config/Build.h"


namespace tgon
{


class TGON_API TRandom
{
public:
	TRandom( ) = delete;
	~TRandom( ) = delete;
	
	static float Range( float min, float max );

private:
	//	WELL Random number generator
	//	It's faster than the mers enne-Twister 40% or so 
	//	cf. http://www.iro.umontreal.ca/~panneton/WELLRNG.html
	static float WELLRNG512a( );
};

inline float TRandom::Range( float min, float max )
{
	return min + ( WELLRNG512a( )*( max-min ));
}


}