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
		Commands
	*/
	virtual void Write( const char* str ) = 0;

	virtual void Write( const wchar_t* str ) = 0;

protected:
	/*
		Cons/Destructor
	*/
	IConsole( ) = default;

	virtual ~IConsole( ) = default;

};


}