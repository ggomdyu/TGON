#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <iostream>
	#include <functional>
	#include <unordered_map>

	#include "WindowStyle.h"
	#include "WindowEvent.h"
#endif


namespace tgon {
	class GenericWindow
	{
		typedef std::function<void()>								WorkProc;
		typedef std::unordered_map<uint32_t, WorkProc>	WorkProcList;

	public:
		explicit						GenericWindow( const WindowStyle& ws );
		virtual							~GenericWindow( );

		void							RegisterEventCallback( const uint32_t targetEvent, const WorkProc& doWork );
		virtual bool					PumpWindowEvent( ) = 0;

	public:
		virtual void					Show( ) = 0;
		virtual void					BringToTop( ) = 0;
		virtual void					SetPosition( const int x, const int y ) = 0;
		virtual void					Move( const int x, const int y ) = 0;
		virtual void					Exit( ) = 0;

		const WindowStyle&		GetWindowStyle( ) const				{ return m_wndStyle; }
		const WorkProcList&		GetEventWorkList( )					{ return m_eventWorkList; }

	private:
		WorkProcList				m_eventWorkList;
		WindowStyle				m_wndStyle;
	};
}

#include "PlatformWindow.h"