/*
* Author : Junho-Cha
* Date : 04/25/2016
* Latest author : 
* Latest date : 
*/

#pragma once
#include "../Platform/Config/Build.h"


namespace tgon
{


template<typename T>
struct TGON_API TEnumStrings
{
	static const char* m_stringArr[];
};

enum struct TErrCode
{
	kFailed,
	kSucceed,
};

template <typename T>
std::string TGON_API GetErrorString( T _enum )
{
	int32_t stringIndex = static_cast<int32_t>( _enum );

	const auto* errString = TEnumStrings<T>::m_stringArr[stringIndex];
	return errString;
}


}