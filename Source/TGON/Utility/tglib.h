/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2016-01-28
* ���� ���� :
* ���� ������ :
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
