/*
* Author : Cha Junho
* Date : 03/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../PlatformInclude.h"

#include <memory>


namespace tgon
{


template <typename DerivedTy>
class TGON_API GenericConsole
{
public:
	//
	// Commands
	//
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

protected:
	// 
	// Ctor/Dtor
	// 
	GenericConsole( ) = delete;
	virtual ~GenericConsole( ) = delete;

private:
	// 
	// Private variables
	//
	enum { BUFFER_SIZE = 256 };
	static std::unique_ptr<char[]> m_buffer;
	static std::unique_ptr<wchar_t[]> m_wideBuffer;
};


} /*namespace tgon*/


#include "GenericConsole.inl"