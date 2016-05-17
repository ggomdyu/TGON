/*
* Author : Junho-Cha
* Date : 01/28/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <iostream>
#include "../Config/SyntaxCompatible.h"

namespace tgon 
{


template<typename T, std::size_t N>
TGON_CONSTEXPR std::size_t array_size( T(&)[N] ) 
{
	return N;
}


}
