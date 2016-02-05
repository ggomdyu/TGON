#pragma once
/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� : ����ȣ
* ���� ������ : 2016-01-09
*/

#include <iostream>

#ifdef PLATFORM_WINDOWS_OS
	#include <windows.h>
#endif

namespace tgon {
namespace Window {

struct WindowEvent
{
private:
	enum PrivateEventTable
	{
	#ifdef PLATFORM_WINDOWS_OS
		TGET_NONE = 0xcccccccc,
		TGET_CREATE = WM_CREATE,
		TGET_SIZE = WM_SIZE,
		TGET_GETFOCUS = WM_SETFOCUS,
		TGET_LOSEFOCUS = WM_KILLFOCUS,
		TGET_MOVE = WM_MOVE,
		TGET_DESTROY = WM_QUIT,
	#endif
	};

public:
	WindowEvent( unsigned int ev = WindowEvent::None ) : m_ev( ev ) {};
	~WindowEvent( ) {};

	enum {
		None = TGET_NONE,
		Create = TGET_CREATE,
		GetFocus = TGET_GETFOCUS,
		LoseFocus = TGET_LOSEFOCUS,
		Size = TGET_SIZE,
		Move = TGET_MOVE,
		Destroy = TGET_DESTROY,
	};

	operator unsigned int( ) const		{ return m_ev; }

private:
	unsigned int m_ev = 0;
};


}
}