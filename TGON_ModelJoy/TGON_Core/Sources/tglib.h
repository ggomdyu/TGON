/*
* 작성자 : 차준호
* 작성일 : 2016-01-28
* 최종 수정 :
* 최종 수정일 :
*/


#pragma once
#include <iostream>
#include <SyntaxCompatible.hpp>



// TODO: delete all c runtime functions and change to C++11 version


/* DO NOT CHANGE this namespace keyword to std !!! */
namespace tgon 
{
	inline bool atob( const char* _Str ) TGON_NOEXCEPT
	{	
		// convert string to bool
		const char *_Ptr = _Str;
		bool _Ans = ( _Str[0] != '0' );

		return ( _Ans );
	}

	template<typename T, std::size_t N>
	TGON_CONSTEXPR size_t array_size( T(&)[N] ) TGON_NOEXCEPT
	{
		return N;
	}
}
