/*
* Author : Junho-Cha
* Date : 04/02/2016
* Latest author :
* Latest date :
* Description : Polymorphic application type
*/


#pragma once
#include "../Config/Platform/PlatformApplication.h"


namespace tgon
{


class TApplication : public ApplicationImpl
{
public:
	static TApplication* Get( )
	{
		static TApplication appInst;
		return &appInst;
	}

protected:
	TApplication( ) {};
	virtual ~TApplication( ) {};
};


}