/*
* 작성자 : 차준호
* 작성일 : 2015-12-07
* 최종 수정 : 차준호
* 최종 수정일 : 2015-12-17
*/

#pragma once
#include "ISystem.h"
#include <Pattern\Singleton.h>

#include <functional>
#include "GenericWindow.h"


namespace tgon {
	class SociableMessage;
	class WindowSystem final : public ISystem
	{
		typedef std::function<void()> EventProc;
		typedef std::unique_ptr<Window> SpWindow;

	public:
		Declare_Static_Singleton( WindowSystem )
			
	public:
		virtual void FrameMove( float elapsedTime ) override;
		virtual void RecvMessage( _In_ const SociableMessage& msg ) override;

		void AddWindowEventCallback( const uint32_t evType, const EventProc& evProc );
		const WindowEvent GetWindowEvent( ) const;

	private:
		WindowSystem( );
		virtual ~WindowSystem( );
		
	private:
		SpWindow m_window;
	};
}