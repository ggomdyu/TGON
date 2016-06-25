// TGON_Test.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "PrecompiledHeader.h"

#include <cassert>
#include <iostream>
#include <stdint.h>


#include <Math/TMatrix4x4.h>
#include <Math/TVector3.h>
#include <d3d9.h>
#include <d3dx9.h>


void SpeedTest( )
{
	int total = 0;
	int repeat = 10;

	for ( int r = 0; r < repeat; ++r )
	{
		DWORD oldTime = GetTickCount( );
		
		for ( int i = 0; i < 10000000; ++i )
		{
			tgon::TMatrix4x4 mat2 =
				tgon::TMatrix4x4::Scale(
					999.f, 999.f, 999.f
				);
		}
	
		DWORD currTime = GetTickCount( );
		total += currTime - oldTime;

		std::cout << "ELAPSED : " << currTime - oldTime << std::endl;
	}

	std::cout << "AVERAGE : " << total / repeat  << std::endl;

}

#include <Window/TWindow.h>
#include <Application/TApplication.h>
#include <Window/Windows/WindowsWindow.h>


#include <Time/TTime.h>
#include <iostream>
#include <Math/TRandom.h>
#include <Math/TMatrix3x3.h>
#include <Math/TMatrix4x4.h>
#include <Console/TConsole.h>

int main( )
{
	using namespace tgon;

    return 0;
}

