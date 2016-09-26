#pragma once
#include "GenericConsole.h"


namespace tgon
{


template<typename DerivedTy>
decltype( GenericConsole<DerivedTy>::m_buffer ) GenericConsole<DerivedTy>::m_buffer( new char[GenericConsole<DerivedTy>::BUFFER_SIZE] );

template<typename DerivedTy>
decltype( GenericConsole<DerivedTy>::m_wideBuffer ) GenericConsole<DerivedTy>::m_wideBuffer( new wchar_t[GenericConsole<DerivedTy>::BUFFER_SIZE] );

template<typename DerivedTy>
inline void GenericConsole<DerivedTy>::Write( const char* str, ... )
{
	va_list vaList;
	va_start( vaList, str );

	// Build string
	vsprintf_s( m_buffer.get( ), BUFFER_SIZE, str, vaList );
	
	// And finally output
	DerivedTy::WriteImpl( m_buffer.get( ));
}

template<typename DerivedTy>
inline void GenericConsole<DerivedTy>::Write( const wchar_t* str, ... )
{
	va_list vaList;
	va_start( vaList, str );

	// Build string
	vswprintf_s( m_wideBuffer.get( ), BUFFER_SIZE, str, vaList );
	
	// And finally output
	DerivedTy::WriteImpl( m_wideBuffer.get( ));
}

template<typename DerivedTy>
inline void GenericConsole<DerivedTy>::WriteLine( const char* str, ... )
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
inline void GenericConsole<DerivedTy>::WriteLine( const wchar_t* str, ... )
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