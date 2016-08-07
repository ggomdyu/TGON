/*
* Author : Cha Junho
* Date : 03/22/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Slate/PlatformConsole.h"


namespace tgon
{


class TGON_API TConsole final :
	public ConsoleImpl
{
/*
	Gets
*/
	// 
	// TApplication singleton interface
	// 
	// @return Return Global TApplication instance
	// 
public:
	static TConsole& Get( )
	{
		static TConsole ret;
		return ret;
	}

/*
	Commands
*/
public:
	void Write( const char* format, ... );

	void Write( const wchar_t* format, ... );

	void WriteLine( const char* format, ... );

	void WriteLine( const wchar_t* format, ... );


/*
	Cons/Destructor
*/
private:
	TConsole( ) = default;

	virtual ~TConsole( ) = default;


/*
	Internal works
*/
private:
	void WriteImpl( const char* format, va_list vaList );
	
	void WriteImpl( const wchar_t* format, va_list vaList );


};


}
