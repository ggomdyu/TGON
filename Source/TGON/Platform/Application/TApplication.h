/*
* Author : Cha Junho
* Date : 04/02/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../Platform/Slate/PlatformApplication.h"


namespace tgon
{

using TApplication = ApplicationImpl;

}


#define TGON_REGISTER_MAINAPP( className )\
int32_t RunApplication( )\
{\
	return className::Main( );\
}