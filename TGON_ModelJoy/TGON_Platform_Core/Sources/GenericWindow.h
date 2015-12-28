#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#include <iostream>
#include <functional>
#include <unordered_map>

#include "WindowStyle.h"
#include "WindowEvent.h"


namespace tgon {
	class GenericWindow
	{
		typedef std::function<void()> EventProc;
		typedef std::unordered_map<uint32_t, EventProc> EventProcMap;

	public:
		explicit GenericWindow( const WindowStyle& );
		virtual ~GenericWindow( );

		virtual void FrameMove( ) = 0;

	public:
		virtual void Show( ) = 0;
		virtual void BringToTop( ) = 0;
		virtual void SetPosition( const int x, const int y ) = 0;
		virtual void Move( const int x, const int y ) = 0;
		virtual void Exit( ) = 0;

		virtual const WindowEvent GetWindowEvent( ) const = 0;

		void AddWindowEventCallback( const uint32_t evType, const EventProc& evProc );

	protected:
		const EventProcMap& GetEventMap( );
		void CallWindowEventProc( const uint32_t evType );

	private:
		EventProcMap m_evMap;
		WindowStyle m_wndStyle;
	};
}

#include "PlatformWindow.h"