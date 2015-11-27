#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <iostream>
	#include "WindowStyle.h"
	#include "Uncopyable.h"
#endif

#include "WindowMessage.h"

NSBEGIN( tgon );
class GenericWindow : private Uncopyable
{
private:
	/*
		This code violate rule of 'make common case fast'...
		but so simple and readable
	*/
	struct EventProxy : private Uncopyable
	{
		std::unordered_set<uint32_t> msgRepo;

		friend bool GenericWindow::EventProxy::operator==( const EventProxy& lhs, const uint32_t uMsg )
		{
			return lhs.msgRepo.find( uMsg ) != lhs.msgRepo.end( );
		}

		friend bool GenericWindow::EventProxy::operator!=( const EventProxy& lhs, const uint32_t uMsg )
		{
			return lhs.msgRepo.find( uMsg ) == lhs.msgRepo.end( );
		}
	};

public:
	explicit GenericWindow( const WindowStyle& ws );
	virtual ~GenericWindow( );

public:
	virtual void Make( ) = 0;

	/* Show */
	virtual void BringToTop( ) = 0;
	virtual void Show( ) = 0;

	/* Move, animate, etc... */
	virtual void SetPosition( const int x, const int y ) = 0; 
	virtual void Move( const int x, const int y ) = 0;
	
public:
	const EventProxy& GetWindowEvent( ) const { return m_eventProxy; }
	const WindowStyle& GetWindowStyle( ) const { return m_ws; }

protected:
	void ResetWindowEvent( ) { m_eventProxy.msgRepo.clear( ); }
	void SetWindowEvent( const uint32_t uMsg ) { m_eventProxy.msgRepo.insert( uMsg ); }

private:
	EventProxy m_eventProxy;
	WindowStyle m_ws;
};
NSEND( );

#ifdef PLATFORM_WINDOWS_OS
	#include "WindowsWindow.h"
#elif PLATFORM_ANDROID_OS
	#include "AndroidWindow.h"
#endif