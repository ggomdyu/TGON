#pragma once
#include "../Config/Platform.h"

#ifdef TGON_PLATFORM_WINDOWS
#include "../MessageBox/Windows/WindowsMessageBox.h"
#elif TGON_PLATFORM_ANDROID
#elif TGON_PLATFORM_LINUX
#endif