/*
* Author : Cha Junho
* Date : 03/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../OSAL/PlatformInclude.h"

#include <boost/noncopyable.hpp>


namespace tgon
{


// todo: Use CRTP
class TGON_API IConsole : 
	private boost::noncopyable
{
	//
	// Commands
	//
public:
	/*
	 * @note Write char* string to console.
	 * @param str String that you want to write to console
	*/
	virtual void Write( /*In*/ const char* str ) = 0;

	/*
	 * @note Write wchar_t* string to console.
	 * @param str String that you want to write to console
	*/
	virtual void Write( /*In*/ const wchar_t* str ) = 0;

	/*
		Ctor/Dtor
	*/
protected:
	IConsole( ) = default;
	
	virtual ~IConsole( ) = default;
};


} /*namespace tgon*/