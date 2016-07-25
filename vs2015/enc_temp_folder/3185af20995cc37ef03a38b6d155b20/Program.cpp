#include "PrecompiledHeader.h"
#include "Program.h"


#include "../../Platform/Main/TMain.h"
#include "TEngineLoop.h"


TGON_REGISTER_MAIN( tgon::Program )


class A :
	public tgon::TObject
{
public:
	TGON_OBJECT( A, std::nullptr_t )
};

class B :
	public A
{
public:
	TGON_OBJECT( B, A )
};

class C :
	public B
{
public:
	TGON_OBJECT( C, B )
};

class C2 :
	public B
{
public:
	TGON_OBJECT( C2, B )
};

int32_t tgon::Program::Main( int32_t argc, char** argv )
{
	B* a = new C2;

	bool w = a->IsKindOf<C>( );


	TEngineLoop engineLoop;

	const int32_t errCode = engineLoop.Execute( argc, argv );
	return errCode;
}