/*
* Author : Junho-Cha
* Date : 04/02/2016
* Latest author :
* Latest date :
* Description : API Sets for cross-platform
*/


#pragma once
#include "../Platform/Slate/PlatformApplication.h"


namespace tgon
{

using TApplication = ApplicationImpl;

}


#define TGON_GENERATE_APP( className )\
namespace tgon\
{\
int32_t RunApplication( )\
{\
	return className::Main( );\
}\
};