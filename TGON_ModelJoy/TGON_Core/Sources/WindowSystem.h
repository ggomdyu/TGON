/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-12-07
* ���� ���� :
* ���� ������ :
*/

#pragma once
#include "Singleton.h"
#include "ISystem.h"

#include "GenericWindow.h"

namespace tgon {
	class SociableMessage;
	class WindowSystem final : public ISystem
	{
		typedef std::shared_ptr<Window> SpWindow;

	public:
		Declare_Static_Singleton( WindowSystem )

	public:
		virtual void				Initialize( ) override;
		virtual void				FrameMove( float elapsedTime ) override;
		virtual void				RecvMessage( _In_ const SociableMessage& msg ) override;
	
	private:
		const SpWindow&		GetWindow( ) const												{ return m_window; }
		void						PumpWindowEvent( );
	
	private:
		WindowSystem( );
		virtual ~WindowSystem( );

	private:
		SpWindow				m_window;
	};
}