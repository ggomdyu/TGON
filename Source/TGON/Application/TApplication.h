/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-03-20
* ���� ���� :
* ���� ������ :
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