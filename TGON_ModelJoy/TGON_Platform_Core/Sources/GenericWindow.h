#pragma once
/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� :
* ���� ������ :
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
	public:
		explicit						GenericWindow( const WindowStyle& ws );
		virtual							~GenericWindow( );

	public:
		virtual void					Show( ) = 0;
		virtual void					BringToTop( ) = 0;
		virtual void					SetPosition( int x, int y ) = 0;
		virtual void					Move( int x, int y ) = 0;
		virtual void					Exit( ) = 0;

	public:
		const WindowStyle&		GetWindowStyle( ) const				{ return m_ws; }
		virtual bool					PumpWindowEvent( ) = 0;									

	protected:
		virtual void					MakeWindow( const WindowStyle& ws ) = 0;

	private:
		WindowStyle					m_ws;
	};
}

#include "PlatformWindow.h"