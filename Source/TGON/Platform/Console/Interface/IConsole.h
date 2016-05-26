/*
* Author : Junho-Cha
* Date : 03/23/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <string>
#include <boost/noncopyable.hpp>
#include "../../../Core/TObject.h"
#include "../../../Platform/Config/Build.h"


namespace tgon
{


class TGON_API IConsole : 
	private boost::noncopyable
{
public:
	virtual void Write( const wchar_t* str ) = 0;
	virtual void Write( const char* str ) = 0;

protected:
	IConsole( ) {};
	virtual ~IConsole( ) = 0 {};
};


}