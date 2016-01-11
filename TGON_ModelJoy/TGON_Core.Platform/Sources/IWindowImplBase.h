/*
* 작성자 : 차준호
* 작성일 : 2016-01-09
* 최종 수정 : 
* 최종 수정일 :
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
	typedef std::unordered_map<uint32_t, EventProc> EventProcTable;

public:
	explicit			IWindowImplBase( const WindowStyle& );
	virtual				~IWindowImplBase( ) = 0;

	virtual void		FrameMove( ) = 0;

public:
	virtual void		Show( ) = 0;
	virtual void		BringToTop( ) = 0;
	virtual void		SetPosition( int x, int y ) = 0;
	virtual void		Move( int x, int y ) = 0;
	virtual void		Exit( ) = 0;

	void				AddEventCallback( uint32_t evType, const EventProc& evProc );

public:
	virtual const WindowEvent		GetWindowEvent( ) const = 0;
	const WindowStyle&				GetWindowStyle( )	 const				{ return m_wndStyle; }


protected:
	void 				CallEventProc( uint32_t evType );


private:
	WindowStyle		m_wndStyle;
	EventProcTable		m_evTable;
};


}