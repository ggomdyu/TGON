/*
* Author : Cha Junho
* Date : 04/25/2016
* Latest author : 
* Latest date : 
*/

#pragma once
#include "../Platform/Config/Build.h"


namespace tgon
{


template<typename _ErrorCodeTy>
struct ErrorStrings
{
	static const wchar_t* m_errStrings[];
};

template<typename _ErrorCodeTy>
inline const wchar_t* GetErrorString( _ErrorCodeTy errEnum )
{
	return ErrorStrings<_ErrorCodeTy>::m_errStrings[static_cast<int>( errEnum )];
}


}