/*
* 작성자 : 차준호
* 작성일 : 2016-03-20
* 최종 수정 :
* 최종 수정일 :
* Description : Polymorphic application type
*/

#pragma once
#include <iostream>
#include <map>
#include <string>
#include "../Config/Platform/PlatformApplication.h"
#include "../Config/Platform/PlatformFwd.h"


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