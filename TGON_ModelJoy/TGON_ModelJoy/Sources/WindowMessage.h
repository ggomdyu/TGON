#pragma once
/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� :
* ���� ������ :
*/

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <unordered_set>
#endif

#ifdef PLATFORM_WINDOWS_OS
	#define MT_NONE 0
	#define MT_CREATE WM_CREATE
	#define MT_SIZE WM_SIZE
	#define MT_MOVE WM_MOVE
	#define MT_DESTROY WM_QUIT
#endif

struct WindowEvent
{
public:
	WindowEvent( const uint32_t _uMsg = WindowEvent::None ) :
			uMsg( _uMsg ) {}

	enum : uint32_t
	{
		None = MT_NONE,
		Create = MT_CREATE,
		Size = MT_SIZE,
		Move = MT_MOVE,
		Destroy = MT_DESTROY,
	};

	uint32_t uMsg = 0;
};