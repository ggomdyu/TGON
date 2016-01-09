#pragma once
/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� :
* ���� ������ :
*/

#include <windows.h>

#ifdef PLATFORM_WINDOWS_OS
	#define ET_NONE 0xcccccccc
	#define ET_CREATE WM_CREATE
	#define ET_SIZE WM_SIZE
	#define ET_MOVE WM_MOVE
	#define ET_DESTROY WM_DESTROY
#endif

struct WindowEvent
{
public:
	WindowEvent( const uint32_t evType = WindowEvent::None ) :
		m_evType( evType ) {}

	enum : uint32_t
	{
		None = ET_NONE,
		Create = ET_CREATE,
		Size = ET_SIZE,
		Move = ET_MOVE,
		Destroy = ET_DESTROY,
	};

	operator uint32_t( ) { return m_evType; }

private:
	uint32_t m_evType = 0;
};