#include "PrecompiledHeader.h"
#include "../../Platform/Main/TMain.h"

#include "../Engine/Executable/TEngine.h"


int32_t tgon::TMain( int32_t argc, char** argv )
{
	TEngine engineLoop;
	
	const int32_t errCode = engineLoop.Execute( argc, argv );
	return 0;
}