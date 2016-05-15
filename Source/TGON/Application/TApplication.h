/*
* Author : Junho-Cha
* Date : 04/02/2016
* Latest author :
* Latest date :
* Description : Polymorphic application type
*/


#pragma once
#include "../Core/TSingleton.h"
#include "../Platform/PlatformApplication.h"
#include "../Config/Build.h"


namespace tgon
{


class TGON_API TApplication : public ApplicationImpl
{
public:
	TGON_OBJECT( TApplication, ApplicationImpl )
	TGON_SINGLETON( TApplication )

protected:
	TApplication( );
	virtual ~TApplication( );
};


}