/*
* Author : Junho-Cha
* Date : 01/10/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../../../Platform/Config/Build.h"


namespace tgon
{


class TGON_API AbstractGraphics : 
	boost::noncopyable
{
protected:
	AbstractGraphics( ) {}
	virtual ~AbstractGraphics( ) = 0 {}
};


}