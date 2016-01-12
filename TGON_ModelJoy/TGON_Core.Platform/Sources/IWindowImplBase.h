/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-09
* ���� ���� : 
* ���� ������ :
*/
#pragma once
#include <functional>
#include <unordered_map>
#include "WindowStyle.h"
#include "WindowEvent.h"


namespace tgon {

class IWindowImplBase
{
protected:
	typedef std::function<void()> EventProc;
	typedef std::unordered_map<unsigned int, EventProc> EventProcTable;

public:
	virtual void		FrameMove( ) = 0;

public:
	virtual void		Show( ) = 0;
	virtual void		BringToTop( ) = 0;
	virtual void		SetPosition( int x, int y ) = 0;
	virtual void		Move( int x, int y ) = 0;
	virtual void		Exit( ) = 0;

	void				AddEventCallback( unsigned int evType, const EventProc& evProc );

public:
	virtual const WindowEvent		GetWindowEvent( ) const = 0;
	const WindowStyle&				GetWindowStyle( )	 const				{ return m_wndStyle; }


protected:
	explicit			IWindowImplBase( const WindowStyle& );
	virtual				~IWindowImplBase( ) = 0;

	void 				CallEventProc( unsigned int evType );


private:
	WindowStyle		m_wndStyle;
	EventProcTable		m_evTable;
};


}