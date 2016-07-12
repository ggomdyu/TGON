/*
* Author : Cha Junho
* Date : 03/23/2016
* Latest author :
* Latest date :
*/


#pragma once
#include "../../../Platform/Config/Build.h"


namespace tgon
{


class TGON_API IConsole : 
	private boost::noncopyable
{
public:
	/*
		Cons/Destructor
	*/
	IConsole( ) = delete;

	virtual ~IConsole( ) = delete;


public:
	/*
		Commands
	*/
	static void Write( const char* str ) {}

	static void Write( const wchar_t* str ) {}
};


}