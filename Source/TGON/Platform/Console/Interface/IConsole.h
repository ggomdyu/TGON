/*
* Author : Junho-Cha
* Date : 03/23/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <boost/noncopyable.hpp>
#include "../../../Core/TObject.h"
#include "../../../Platform/Config/Build.h"


namespace tgon
{


class TGON_API IConsole : 
	private boost::noncopyable
{
public:
	static void Write( const wchar_t* str ) {};
	static void Write( const char* str ) {};

protected:
	IConsole( ) = delete;
	virtual ~IConsole( ) = delete;
};


}