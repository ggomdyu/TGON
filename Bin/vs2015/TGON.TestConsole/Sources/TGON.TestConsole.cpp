#include "PrecompiledHeader.h"


#include <iostream>
#include <vector>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <Core/Math/TMath.h>
#include <Core/Object/Object.h>

#include <Windows.h>


using namespace tgon;


#define MAKE_TO_STRING( type ) #type

class Wow : 
	public Object
{
public:
	TGON_GENERATE_OBJECT_INTERFACE( Wow, Object )
};

template <std::size_t N>
void foo( const char( &str )[N] )
{
	std::cout << N;
}

void Do1( )
{
	int ret = 0;
	for ( int r = 0; r < 10; ++r )
	{
		auto b = GetTickCount( );
		for ( int i = 0; i < 1000000000; ++i )
		{
			try
			{
				++ret;
			}
			catch ( std::runtime_error re )
			{
			}
		}
		auto e = GetTickCount( );
		std::cout << e - b << "\n";
	}
}

void Do2( )
{
	int ret = 0;
	for ( int r = 0; r < 10; ++r )
	{
		auto b = GetTickCount( );
		for ( int i = 0; i < 1000000000; ++i )
		{
			try
			{
				++ret;
			}
			catch ( std::runtime_error re )
			{
			}
		}
		auto e = GetTickCount( );
		std::cout << e - b << "\n";
	}
}

template <typename... Args>
void foo( Args&&... args )
{
	std::cout << "1";
}

int main( int argc, char* argv[] )
{
	//
	//std::cout << a.IsAbstract( ) << std::endl;
	//std::cout << a.IsArray( ) << std::endl;
	//std::cout << a.IsClass ( ) << std::endl;
	//std::cout << a.IsConst( ) << std::endl;
	//std::cout << a.IsEnum( ) << std::endl;
	//std::cout << a.IsMemberFunctionPointer( ) << std::endl;
	//std::cout << a.IsPOD( ) << std::endl;
	//std::cout << a.IsPointer( ) << std::endl;
	//std::cout << a.IsReference( ) << std::endl;
	//std::cout << a.IsMemberFunctionPointer( ) << std::endl;

	return 0;
}