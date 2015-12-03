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
	#include "Uncopyable.h"
#endif

#include "GenericWindow.h"

NSBEGIN( tgon );
class GenericApplication : private Uncopyable
{
public:
	static void AddWindow( const std::string& key, _In_ const std::shared_ptr<Window>& window );
	static const std::shared_ptr<Window> GetWindow( _In_ const std::string& key );

private:
	GenericApplication( ) = delete;
	virtual ~GenericApplication( ) = delete;

private:
	static std::map<std::string, std::shared_ptr<Window>> m_wndRepository;
};
NSEND( );

#ifdef PLATFORM_WINDOWS_OS
	#include "WindowsApplication.h"
#elif PLATFORM_ANDROID_OS
	#include "AndroidApplication.h"
#endif