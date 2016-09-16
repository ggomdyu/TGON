/*
* Author : Cha Junho
* Date : 03/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "APlatformConsole.h"


namespace tgon
{


template<typename DerivedTy>
decltype( APlatformConsole<DerivedTy>::m_buffer ) APlatformConsole<DerivedTy>::m_buffer( new char[APlatformConsole<DerivedTy>::BUFFER_SIZE] );

template<typename DerivedTy>
decltype( APlatformConsole<DerivedTy>::m_wideBuffer ) APlatformConsole<DerivedTy>::m_wideBuffer( new wchar_t[APlatformConsole<DerivedTy>::BUFFER_SIZE] );

template<typename DerivedTy>
inline void APlatformConsole<DerivedTy>::Write( const char* str, ... )
{
	va_list vaList;
	va_start( vaList, str );

	// Build string
	vsprintf_s( m_buffer.get( ), BUFFER_SIZE, str, vaList );
	
	// And finally output
	DerivedTy::WriteImpl( m_buffer.get( ));
}

template<typename DerivedTy>
inline void APlatformConsole<DerivedTy>::Write( const wchar_t* str, ... )
{
	va_list vaList;
	va_start( vaList, str );

	// Build string
	vswprintf_s( m_wideBuffer.get( ), BUFFER_SIZE, str, vaList );
	
	// And finally output
	DerivedTy::WriteImpl( m_wideBuffer.get( ));
}

template<typename DerivedTy>
inline void APlatformConsole<DerivedTy>::WriteLine( const char* str, ... )
{
	va_list vaList;
	va_start( vaList, str );

	// Build string
	vsprintf_s( m_buffer.get( ), BUFFER_SIZE, str, vaList );
	
	// And finally output
	DerivedTy::WriteImpl( m_buffer.get( ));
	DerivedTy::WriteImpl( "\n" );
}

template<typename DerivedTy>
inline void APlatformConsole<DerivedTy>::WriteLine( const wchar_t* str, ... )
{
	va_list vaList;
	va_start( vaList, str );

	// Build string
	vswprintf_s( m_wideBuffer.get( ), BUFFER_SIZE, str, vaList );
	
	// And finally output
	DerivedTy::WriteImpl( m_wideBuffer.get( ));
	DerivedTy::WriteImpl( "\n" );
}


} /*namespace tgon*/