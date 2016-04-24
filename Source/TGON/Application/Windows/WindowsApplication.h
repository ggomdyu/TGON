/*
* Author : Junho-Cha
* Date : 03/20/2016
* Latest author :
* Latest date :
* Description : Abstracte Windows syetem API
*/

#pragma once
#include "../Layered/LayeredApplication.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN


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
	virtual bool DispatchEvent(
		_Out_ enum struct WindowEvent* const ) override;
	virtual struct TSystemBatteryInfo GetPowerInfo( ) override;
	virtual void GetScreenSize(
		_Out_ int32_t* width,
		_Out_ int32_t* height ) override;

	HINSTANCE GetInstanceHandle( ) const;

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