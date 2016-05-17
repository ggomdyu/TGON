/*
* Author : Junho-Cha
* Date : 03/23/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <string>
#include <boost/noncopyable.hpp>
#include "../../../Core/TObject.h"
#include "../../../Platform/Config/Build.h"


namespace tgon
{


class TGON_API IConsole : 
	private boost::noncopyable
{
public:
	virtual void Write( ) = 0;
	virtual void WriteLine( ) = 0;

protected:
	template<class T>
	void FillBuffer( const T& arg );
	void FillBuffer( const wchar_t* arg );
	void FillBuffer( const char* arg );
	void ClearBuffer( );
	const std::wstring& GetBuffer( ) const;

protected:
	IConsole( ) {};
	virtual ~IConsole( ) = 0 {};

private:
	std::wstring m_buf;
};


template<class T>
inline void IConsole::FillBuffer( const T& arg ) 
{
	m_buf += std::to_wstring( arg );
};


inline void IConsole::FillBuffer( const wchar_t* arg )
{
	m_buf += arg;
}


inline const std::wstring& IConsole::GetBuffer( ) const 
{
	return m_buf;
}


inline void IConsole::ClearBuffer( )
{
	m_buf.clear( );
}


}