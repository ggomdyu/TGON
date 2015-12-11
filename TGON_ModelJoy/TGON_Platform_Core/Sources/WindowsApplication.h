/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-11-12
* ���� ���� : 
* ���� ������ : 
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