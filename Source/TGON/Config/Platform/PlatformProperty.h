/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-04-01
* ���� ���� :
* ���� ������ :
*/

#pragma once
#include "Platform.h"

#ifdef TGON_PLATFORM_WINDOWS
	#include "../Property/Windows/WindowsProperty.h"
#elif TGON_PLATFORM_ANDROID
	#include "../Property/Android/AndroidProperty.h"
#endif