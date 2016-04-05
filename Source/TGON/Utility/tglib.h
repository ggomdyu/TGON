/*
* 작성자 : 차준호
* 작성일 : 2016-01-28
* 최종 수정 :
* 최종 수정일 :
*/


#pragma once
#include <iostream>
#include "../Compiler/SyntaxCompatible.hpp"

namespace tgon 
{


template<typename T, std::size_t N>
TGON_CONSTEXPR size_t array_size( T(&)[N] ) 
{
	return N;
}


}
