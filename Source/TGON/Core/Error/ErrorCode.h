/*
* Author : Cha Junho
* Date : 04/25/2016
* Latest author : 
* Latest date : 
* Description : Error code generator
*/

#pragma once

namespace tgon
{


template<typename ErrorCodeTy>
struct ErrorStrings
{
	static const wchar_t* m_errStrings[];
};

template<typename ErrorCodeTy>
inline const wchar_t* GetErrorString( ErrorCodeTy errEnum )
{
	return ErrorStrings<ErrorCodeTy>::m_errStrings[static_cast<int>( errEnum )];
}


}