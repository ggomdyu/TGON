/*
* 작성자 : 차준호
* 작성일 : 2016-03-20
* 최종 수정 :
* 최종 수정일 :
* Description : Abstracted Windows API & Util
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
	virtual void DispatchEvent( _Out_ enum struct WindowEvent* const ) override;
	
	HINSTANCE GetInstanceHandle( ) const;

	virtual void GetScreenSize( int32_t* const width,
							    int32_t* const height ) override;
	
	virtual void GetCursorPosition( int32_t* const x,
								    int32_t* const y ) override;
	
	virtual struct TSystemBatteryInfo GetPowerInfo( ) override;

private:
	HINSTANCE m_instanceHandle;
};


}


#include "WindowsApplication.hpp"