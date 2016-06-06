/*
* Author : Junho-Cha
* Date : 06/02/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <Application/TApplication.h>
#include "Tgon_ModelJoy.h"


namespace tgon
{


class Program
{
public:
	Program( );
	~Program( );

	static int32_t Main( )
	{
		auto windowForm = std::make_shared<Tgon_ModelJoy>( );
		return TApplication::Run( windowForm );
	}
};


}