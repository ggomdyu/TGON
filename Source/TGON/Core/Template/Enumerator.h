/*
* Author : Junho-Cha
* Date : 06/20/2016
* Latest author :
* Latest date :
*/


#pragma once
#include <type_traits>


namespace tgon
{


template <typename Ty>
constexpr std::underlying_type_t<Ty> ToUnderlying( Ty enumElem )
{
	return static_cast<std::underlying_type_t<Ty>>( enumElem );
}


} /*namespace tgon*/