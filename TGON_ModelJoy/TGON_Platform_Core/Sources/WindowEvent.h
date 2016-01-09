#pragma once
/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� :
* ���� ������ :
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
	explicit WindowEvent( const uint32_t _msg = WindowEvent::None ) :
			msg( _msg ) {}

	enum : uint32_t
	{
		None = ET_NONE,
		Create = ET_CREATE,
		Size = ET_SIZE,
		Move = ET_MOVE,
		Destroy = ET_DESTROY,
	};

	uint32_t msg = 0;
};