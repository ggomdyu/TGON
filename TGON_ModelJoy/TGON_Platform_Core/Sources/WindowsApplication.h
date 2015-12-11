/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 : 
* 최종 수정일 : 
*/
#pragma once
#include "GenericApplication.h"

namespace tgon {
	class WindowsApplication;
	typedef WindowsApplication Application;

	class WindowsApplication final : public GenericApplication
	{
	public:
		static	bool			ResponseMessage( );
		static	HINSTANCE	GetInstanceHandle( ) { return m_hInstance; }

	private:
		WindowsApplication( ) = delete;
		virtual ~WindowsApplication( ) = delete;

	private:
		static HINSTANCE m_hInstance;
	};
}