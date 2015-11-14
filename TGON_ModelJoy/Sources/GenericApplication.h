/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 : 
* 최종 수정일 : 
*/

#pragma once
#ifndef TGON_USE_PRECOMPILED_HEADER
	#include <map>
#endif

#include "GenericWindow.h"

NSBEGIN( tgon );
class GenericApplication : private Uncopyable
{
public:
	static void AddWindow( const std::string& key,
						   _In_ const std::shared_ptr<PlatformWindow>& window );
	static const std::shared_ptr<PlatformWindow> GetWindow( const std::string& key );

private:
	static std::map<std::string, std::shared_ptr<PlatformWindow>> m_windowRepository;
};
NSEND( );

#ifdef PLATFORM_WINDOWS_OS
	#include "WindowsApplication.h"
#elif PLATFORM_ANDROID_OS
	#include "AndroidApplication.h"
#endif