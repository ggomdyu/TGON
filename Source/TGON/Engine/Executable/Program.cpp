#include "PrecompiledHeader.h"
#include "Program.h"


#include "../../Platform/Main/TMain.h"
#include "TEngineLoop.h"


TGON_REGISTER_MAIN( tgon::Program )


int32_t tgon::Program::Main( int32_t argc, char** argv )
{
	TEngineLoop engineLoop;

	const int32_t errCode = engineLoop.Execute( argc, argv );
	return errCode;
}