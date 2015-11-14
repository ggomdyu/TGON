#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include "Uncopyable.h"
	#include "WindowStyle.h"
#endif

NSBEGIN( tgon );
class GenericWindow : private Uncopyable
{
public:
	explicit GenericWindow( const WindowStyle& ws );
	virtual ~GenericWindow( );

public:
	virtual void Make( ) = 0;
	void SetCurrentMessage( const uint32_t uMsg );

	uint32_t GetCurrentMessage( ) const;
	const WindowStyle& GetWindowStyle( ) const;

public:
	/* Show */
	virtual void BringToTop( ) = 0;
	virtual void Show( ) = 0;

	/* Move, animate, etc... */
	virtual void SetPosition( const int x, const int y ) = 0;
	virtual void Move( const int x, const int y ) = 0;

private:
	uint32_t m_nMsgType;
	WindowStyle m_ws;
};
NSEND( );

#ifdef PLATFORM_WINDOWS_OS
	#include "WindowsWindow.h"
#elif PLATFORM_ANDROID_OS
	#include "AndroidWindow.h"
#endif