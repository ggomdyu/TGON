#pragma once
#include "../Config/Platform/Platform.h"

#ifdef TGON_PLATFORM_WINDOWS
	#include "../../Math/Windows/WindowsMath.h"
#elif TGON_PLATFORM_ANDROID
	#include "../../Math/Windows/AndroidMath.h"
#elif TGON_PLATFORM_LINUX
	#include "../../Math/Windows/LinuxMath.h"
#endif