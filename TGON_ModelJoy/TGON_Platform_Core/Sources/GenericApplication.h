/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 : 
* 최종 수정일 : 
*/

#pragma once
#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <map>
	#include <memory>
#endif

#include "GenericWindow.h"

namespace tgon {
	class GenericApplication
	{
	protected:
		typedef std::shared_ptr<Window>								sspWindow;
		typedef std::map<std::string, std::shared_ptr<Window>>		WindowContainer;

	public:
		static void					AddWindow( _In_ const std::string& key, _In_ const sspWindow& window );
		static const sspWindow	GetWindow( _In_ const std::string& key );

	private:
		GenericApplication( ) = delete;
		virtual ~GenericApplication( ) = delete;

	private:
		static WindowContainer m_wndRepo;
	};
}

#ifdef PLATFORM_WINDOWS_OS
	#include "WindowsApplication.h"
#elif PLATFORM_ANDROID_OS
	#include "AndroidApplication.h"
#endif