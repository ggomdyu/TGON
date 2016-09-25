#include "PrecompiledHeader.h"


#include <iostream>
#include <vector>
#include <cstdint>
#include <functional>
#include <iostream>
#include <string>
#include <Core/Math/TMath.h>
#include <Core/Object/Object.h>



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

#include <Windows.h>

int main( int argc, char* argv[] )
{
	class A {};
	class B : public A {};
	const char* n = "A";


	B b;
	A a = b;


	std::cout << GetType<A >( ).GetName( );


	/*for ( int r = 0; r < 10; ++r )
	{
		auto b = GetTickCount( );
		for ( int i = 0; i < 100000000; ++i )
		{
			const char* name = typeid( A ).name( );
		}
		auto e = GetTickCount( );
		std::cout << e - b << "\n";
	}
*/
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