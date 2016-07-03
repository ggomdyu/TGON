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
	const auto errStringNum = 
		typename std::underlying_type<D3D9ErrorCode>::type( errEnum );

	return ErrorStrings<_ErrorCodeTy>::m_errStrings[errStringNum];
}


}