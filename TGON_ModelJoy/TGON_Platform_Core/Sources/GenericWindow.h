#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <iostream>
	#include <unordered_set>

	#include "WindowStyle.h"
	#include "WindowEvent.h"
#endif

namespace tgon {
	class GenericWindow
	{
		typedef std::unordered_set<uint32_t> WndEventRepo;

	public:
		explicit						GenericWindow( const WindowStyle& ws );
		virtual							~GenericWindow( );

	public:
		virtual void					Show( ) = 0;
		virtual void					BringToTop( ) = 0;
		virtual void					SetPosition( const int x, const int y ) = 0;
		virtual void					Move( const int x, const int y ) = 0;
		virtual void					Exit( ) = 0;

	public:
		const WindowStyle&		GetWindowStyle( ) const									{ return m_ws; }
		const WndEventRepo&		GetWindowEventRepo( ) const							{ return m_wndEventRepo; }

		virtual bool					PumpWindowEvent( ) = 0;
		void							ClearAllWindowEvent( )									{ m_wndEventRepo.clear( ); }									

	protected:
		virtual void					MakeWindow( const WindowStyle& ws ) = 0;
		void							InsertOccuredEvent( uint32_t eventType )			{ m_wndEventRepo.insert( eventType ); }

	private:
		WindowStyle					m_ws;
		WndEventRepo				m_wndEventRepo;
	};
}

#ifdef PLATFORM_WINDOWS_OS
	#include "WindowsWindow.h"
#elif PLATFORM_ANDROID_OS
	#include "AndroidWindow.h"
#endif