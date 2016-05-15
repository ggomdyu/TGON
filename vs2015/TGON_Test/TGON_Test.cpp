// TGON_Test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"

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
#include <Window/WindowEvent.h>
#include <Window/Windows/WindowsWindow.h>


#include <Time/TTime.h>
#include <iostream>

int main( )
{
	using namespace tgon;
	using namespace std;
	using namespace chrono;

	while ( true )
	{
	}

    return 0;
}

