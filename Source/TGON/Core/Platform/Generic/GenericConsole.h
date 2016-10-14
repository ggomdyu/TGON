/*
* Author : Cha Junho
* Date : 03/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../OSAL/PlatformInclude.h"

#include <memory>


namespace tgon
{


template <typename DerivedTy>
class TGON_API GenericConsole
{
	/* 
	 * Ctor/Dtor
	*/ 
protected:
	GenericConsole( ) = delete;
	~GenericConsole( ) = delete;

	/*
	 * Commands
	*/
public:
	/*
	 * @note			Write string to console.
	 * @param	str		String which you want to write to console
	*/
	static void Write( /*In*/ const char* str, ... );
	static void Write( /*In*/ const wchar_t* str, ... );
	
	/*
	 * @note			Write string to console and jump to next line.
	 * @param	str		String which you want to write to console
	*/
	static void WriteLine( /*In*/ const char* str, ... );
	static void WriteLine( /*In*/ const wchar_t* str, ... );

	/* 
	 * Variables
	*/
private:
	enum { BUFFER_SIZE = 256 };
	static std::unique_ptr<char[]> m_buffer;
	static std::unique_ptr<wchar_t[]> m_wideBuffer;
};


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

