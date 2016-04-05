/*
* 작성자 : 차준호
* 작성일 : 2016-04-01
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "Platform.h"

#ifdef TGON_PLATFORM_WINDOWS
	#include "../Property/Windows/WindowsProperty.h"
#elif TGON_PLATFORM_ANDROID
	#include "../Property/Android/AndroidProperty.h"
#endif