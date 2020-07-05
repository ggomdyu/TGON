#pragma once

#define TGON_PLATFORM_NAME Windows
#define TGON_PLATFORM_WINDOWS 1
#define TGON_GRAPHICS_OPENGL 1

#ifdef _WINDLL
#	ifdef TGON_API_EXPORT
#		define TGON_API __declspec(dllexport)
#	else
#		define TGON_API __declspec(dllimport)
#	endif
#else
#	define TGON_API
#endif