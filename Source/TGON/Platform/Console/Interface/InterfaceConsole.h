/*
* Author : Cha Junho
* Date : 03/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../../Platform/Config/Build.h"

#include <boost/noncopyable.hpp>


namespace tgon
{


class TGON_API InterfaceConsole : 
	private boost::noncopyable
{
/*
	Commands
*/
public:
	//
	// Write char* string to console.
	//
	// @param str String that you want to write to console
	//
	virtual void Write( /*In*/ const char* str ) = 0;

	//
	// Write wchar_t* string to console.
	//
	// @param str String that you want to write to console
	//
	virtual void Write( /*In*/ const wchar_t* str ) = 0;

/*
	Cons/Destructor
*/
protected:
	InterfaceConsole( ) = default;

	virtual ~InterfaceConsole( ) = default;
};


}