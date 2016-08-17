#include "PrecompiledHeader.h"
#include "TConsole.h"


void tgon::TConsole::Write( const char* format, ... )
{
	va_list vaList;
	va_start( vaList, format );

	this->WriteImpl( format, vaList );

	va_end( vaList );
}

void tgon::TConsole::Write( const wchar_t* format, ... )
{
	va_list vaList;
	va_start( vaList, format );

	this->WriteImpl( format, vaList );

	va_end( vaList );
}

void tgon::TConsole::WriteLine( const char* format, ... )
{
	va_list vaList;
	va_start( vaList, format );

	this->WriteImpl( format, vaList );

	va_end( vaList );

	ConsoleImpl::Write( "\n" );

}

void tgon::TConsole::WriteLine( const wchar_t* format, ... )
{
	va_list vaList;
	va_start( vaList, format );

	this->WriteImpl( format, vaList );

	va_end( vaList );

	ConsoleImpl::Write( "\n" );
}

void tgon::TConsole::WriteImpl( const char* format, va_list vaList )
{
	const int bufferSize = 256;
	char buffer[bufferSize] {0};

	// Build string
	vsprintf_s( buffer, bufferSize, format, vaList );

	// And output to console
	ConsoleImpl::Write( buffer );
}

void tgon::TConsole::WriteImpl( const wchar_t* format, va_list vaList )
{
	const int bufferSize = 256;
	wchar_t buffer[bufferSize] {0};

	// Build string
	vswprintf_s( buffer, bufferSize, format, vaList );

	// And output to console
	ConsoleImpl::Write( buffer );
}
