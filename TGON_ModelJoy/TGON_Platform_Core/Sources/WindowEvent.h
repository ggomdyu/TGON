#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#ifndef TGON_USE_PRECOMPILED_HEADER
	//#include <stdint.h>
#endif
	#include <windows.h>

#ifdef PLATFORM_WINDOWS_OS
	#define ET_NONE 0
	#define ET_CREATE WM_CREATE
	#define ET_SIZE WM_SIZE
	#define ET_MOVE WM_MOVE
	#define ET_DESTROY WM_DESTROY
#endif

struct WindowEvent
{
public:
	WindowEvent( const uint32_t _uMsg = WindowEvent::None ) :
			uMsg( _uMsg ) {}

	enum : uint32_t
	{
		None = ET_NONE,
		Create = ET_CREATE,
		Size = ET_SIZE,
		Move = ET_MOVE,
		Destroy = ET_DESTROY,
	};

	uint32_t uMsg = 0;
};