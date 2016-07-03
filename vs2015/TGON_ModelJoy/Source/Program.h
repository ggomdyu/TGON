/*
* Author : Cha Junho
* Date : 06/02/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <Application/TApplication.h>
#include "TgonModelJoyForm.h"


namespace tgon
{


class Program
{
public:
	static int32_t Main( )
	{
		auto form = std::make_shared<TgonModelJoyForm>( );
		return TApplication::Run( *form.get( ));
	}
};


}