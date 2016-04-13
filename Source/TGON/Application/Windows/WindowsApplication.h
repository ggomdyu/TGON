/*
* Author : Junho-Cha
* Date : 2016-03-20
* Latest author :
* Latest date :
* Description : Abstracted Windows API & Util
*/

#pragma once
#include "../Layered/LayeredApplication.h"

#include <minwindef.h>


namespace tgon
{


class WindowsApplication;
typedef WindowsApplication ApplicationImpl;


class WindowsApplication : public LayeredApplication
{
protected:
	WindowsApplication( ) :
		m_instanceHandle( GetModuleHandle( NULL )) {}
	
	virtual ~WindowsApplication( ) {}

public:
	virtual void DispatchEvent( _Out_ enum struct WindowEvent* const ) override;
	
	HINSTANCE GetInstanceHandle( ) const;

	virtual void GetScreenSize( _Out_ int32_t* const width,
								_Out_ int32_t* const height ) override;

	virtual struct TSystemBatteryInfo GetPowerInfo( ) override;

private:
	HINSTANCE m_instanceHandle;
};


inline HINSTANCE WindowsApplication::GetInstanceHandle( ) const
{
	return m_instanceHandle;
}


inline void WindowsApplication::GetScreenSize(
	int32_t* const width,
	int32_t* const height )
{
	*width = GetSystemMetrics( SM_CXSCREEN );
	*height = GetSystemMetrics( SM_CYSCREEN );
}


}