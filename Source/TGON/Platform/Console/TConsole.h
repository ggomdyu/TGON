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


class TGON_API TConsole :
	public ConsoleImpl
{
public:
	static TConsole& Get( )
	{
		static TConsole ret;
		return ret;
	}

public:
	/*
		Commands
	*/
	// Write
	void Write( const char* format, ... );

	void Write( const wchar_t* format, ... );

	void WriteLine( const char* format, ... );

	void WriteLine( const wchar_t* format, ... );


protected:
	/*
		Cons/Destructor
	*/
	TConsole( ) = default;

	virtual ~TConsole( ) = default;


private:
	void WriteImpl( const char* format, va_list vaList );
	
	void WriteImpl( const wchar_t* format, va_list vaList );


};


}
