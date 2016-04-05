#pragma once
#include "GenericPlatformConsole.h"


template<class T>
TGON_FORCEINLINE void tgon::ConsoleBaseImpl::FillBuffer( const T& arg ) 
{
	m_buf += std::to_wstring( arg );
};


TGON_FORCEINLINE void tgon::ConsoleBaseImpl::FillBuffer( const wchar_t* arg ) 
{
	m_buf += arg;
}


TGON_FORCEINLINE const wchar_t* tgon::ConsoleBaseImpl::GetBuffer( ) const 
{
	return m_buf.c_str();
}


TGON_FORCEINLINE size_t tgon::ConsoleBaseImpl::GetBufferLength( ) const 
{
	return m_buf.length( );
}


TGON_FORCEINLINE void tgon::ConsoleBaseImpl::ClearBuffer( ) 
{
	m_buf.clear( );
}