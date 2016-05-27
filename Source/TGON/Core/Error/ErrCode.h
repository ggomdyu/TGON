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


enum struct ErrCode
{
	kFailed,
	kSucceed,
};

template<typename _Ty>
struct TGON_API EnumStrings
{
	TGON_API static const char* m_stringArr[];
};

template <typename _Ty>
std::string TGON_API GetErrorString( _Ty _enum )
{
	int32_t errStrIndex = static_cast<int32_t>( _enum );

	const auto* errString = EnumStrings<_Ty>::m_stringArr[errStrIndex];
	return errString;
}


}