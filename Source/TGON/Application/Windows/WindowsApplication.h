/*
* Author : Junho-Cha
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Windows syetem API implement
*/

#pragma once
#include "../Interface/IApplication.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN


namespace tgon
{


class WindowsApplication;
using ApplicationImpl = WindowsApplication;

class TGON_API WindowsApplication : 
	public IApplication
{
public:
	TGON_OBJECT( WindowsApplication, IApplication )

public:
	virtual bool DispatchEvent( enum struct WindowEvent* ) override;
	virtual void GetScreenSize( int32_t* width, int32_t* height ) override;
	virtual struct TSystemBatteryInfo GetPowerInfo( ) override;

	HINSTANCE GetInstanceHandle( ) const;

protected:
	WindowsApplication( );
	virtual ~WindowsApplication( );

private:
	MSG m_msg;
	HINSTANCE m_instanceHandle;
};


inline HINSTANCE WindowsApplication::GetInstanceHandle( ) const
{
	return m_instanceHandle;
}

inline void WindowsApplication::GetScreenSize(
	int32_t* width, 
	int32_t* height )
{
	*width = GetSystemMetrics( SM_CXSCREEN );
	*height = GetSystemMetrics( SM_CYSCREEN );
}


}