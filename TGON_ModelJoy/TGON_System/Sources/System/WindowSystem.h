/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-12-07
* ���� ���� : ����ȣ
* ���� ������ : 2015-12-17
*/

#pragma once
#include "ISystem.h"
#include <Pattern\Singleton.h>

#include <functional>
#include "tgWindow.h"


namespace tgon {


class SociableMessage;
class WindowSystem final : public ISystem
{
	typedef std::function<void()> EventProc;

public:
	Declare_Static_Singleton( WindowSystem )
			
public:
	virtual void		FrameMove( float elapsedTime ) override;
	virtual void		RecvMessage( _In_ const SociableMessage& msg ) override;

public:
	const WindowEvent	GetWindowEvent( ) const	{ return m_window.GetWindowEvent( ); }
	Window&				GetWindow( )					{ return m_window; }

private:
						WindowSystem( );
	virtual				~WindowSystem( );
		
private:
	Window		m_window;
};


inline WindowSystem*		GetWindowSystem( )	{ return WindowSystem::GetInstance( ); }

}