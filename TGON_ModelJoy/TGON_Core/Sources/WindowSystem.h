/*
* 작성자 : 차준호
* 작성일 : 2015-12-07
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "Singleton.h"
#include "ISystem.h"

#include "GenericWindow.h"

namespace tgon {
	class SociableMessage;
	class WindowSystem final : public ISystem
	{
		Implement_Singleton( WindowSystem )


		typedef std::shared_ptr<Window> SpWindow;

	public:
		virtual void				Initialize( ) override;
		virtual void				FrameMove( ) override;

		virtual void				RecvMessage( _In_ const SociableMessage& msg ) override;
		bool						PumpWindowEvent( );
		
	public:
		bool						IsEventOccured( const uint32_t eventType );
		
	private:
		const SpWindow&		GetWindow( ) const													{ return m_window; }
		void						ClearAllWindowEvents( )											{ m_window->ClearAllWindowEvent( ); }
	
	private:
		WindowSystem( );
		virtual ~WindowSystem( );

	private:
		SpWindow				m_window;
	};
}