#include "PrecompiledHeader.h"
#include "TMain.h"

#include "../Engine/Engine.h"


namespace tgon
{


int main( int argc, char** argv )
{
	// Singleton on demand
	{
	}

	// Start engine loop
	{
		Engine engineLoop;
		return engineLoop.Execute( argc, argv );

		//try
		//{
		//}
		//catch ( std::runtime_error re )
		//{
		//
		//}
	}
}


} /*namespace tgon*/