/*
* Author : Cha Junho
* Date : 03/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../OSAL/PlatformInclude.h"

#include <boost/noncopyable.hpp>
#include <memory>


namespace tgon
{


template <typename DerivedTy>
class TGON_API APlatformConsole : 
	private boost::noncopyable
{
	//
	// Commands
	//
public:
	/*
	 * @note		Write string to console.
	 * @param	str	String which you want to write to console
	*/
	void Write( /*In*/ const char* str, ... );
	void Write( /*In*/ const wchar_t* str, ... );

	/*
	* @note			Write string to console and jump to next line.
	* @param	str	String which you want to write to console
	*/
	void WriteLine( const char* str, ... );		
	void WriteLine( const wchar_t* str, ... );

	//
	// Internal works
	//
private:
	void WriteImpl( const char* str );
	void WriteImpl( const wchar_t* str );

	// 
	// Ctor/Dtor
	// 
protected:
	APlatformConsole( ) = default;
	virtual ~APlatformConsole( ) = default;

	// 
	// Private variables
	//
private:
	enum { BUFFER_SIZE = 256 };
	static std::unique_ptr<char[]> m_buffer;
	static std::unique_ptr<wchar_t[]> m_wideBuffer;
};


} /*namespace tgon*/


#include "APlatformConsole.inl"