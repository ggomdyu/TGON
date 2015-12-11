/*
* 작성자 : 차준호
* 작성일 : 2015-12-07
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "Singleton.h"
#include "ISociable.h"
#include "ISystem.h"

#include "GenericWindow.h"
#include "MsgManager.h"

namespace tgon {
	class WindowSystem final : public ISystem
	{
		Implement_Singleton( WindowSystem )
		typedef std::shared_ptr<Window> SpWindow;

	public:
		virtual void				Initialize( ) override;
		virtual void				FrameMove( ) override;

		virtual void				RecvMessage( _In_ const CommMessage& msg ) override;
		bool						PumpWindowEvent( );
		
	public:
		bool						IsEventOccured( const uint32_t eventType );
		void						ClearAllWindowEvents( )											{ m_window->ClearAllWindowEvent( ); }
		const SpWindow&		GetWindow( ) const												{ return m_window; }
		
	private:
		WindowSystem( );
		virtual ~WindowSystem( );

	private:
		SpWindow				m_window;
	};
}