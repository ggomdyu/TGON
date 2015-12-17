/*
* 작성자 : 차준호
* 작성일 : 2015-12-07
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "Singleton.h"
#include "ISystem.h"

#include "RTTI.h"
#include "GenericWindow.h"

namespace tgon {
	class SociableMessage;
	class WindowSystem final : public ISystem
	{
		typedef std::unique_ptr<Window> SpWindow;

	public:
		Declare_RTTI( )
		Declare_Static_Singleton( WindowSystem )

	public:
		virtual void				Initialize( ) override;
		virtual void				FrameMove( float elapsedTime ) override;
		virtual void				RecvMessage( _In_ const SociableMessage& msg ) override;
	
	private:
		void						PumpWindowEvent( );
	
	private:
		WindowSystem( );
		virtual ~WindowSystem( );

	private:
		SpWindow				m_window;
	};
}