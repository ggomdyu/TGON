/*
* Author : Cha Junho
* Date : 07/01/2016
* Latest author :
* Latest date :
*/


#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#	undef WIN32_LEAN_AND_MEAN
#endif

namespace tgon
{


class WindowsConsoleHelper final
{
public:
	static WindowsConsoleHelper* Get( )
	{
		static WindowsConsoleHelper wch;
		return &wch;
	}

	HANDLE GetConsoleHandle( ) const;

private:
	WindowsConsoleHelper( );
	~WindowsConsoleHelper( );

private:
	HANDLE m_outputHandle;
};


}

inline HANDLE tgon::WindowsConsoleHelper::GetConsoleHandle( ) const
{
	return m_outputHandle;
}