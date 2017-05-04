/**
 * @filename    TEnumerator.h
 * @author   ggomdyu
 * since    06/20/2016
 */

#pragma once
#include <type_traits>

namespace tgon
{

template <typename Ty>
constexpr std::underlying_type_t<Ty> Underlying(Ty enumElem)
{
	return static_cast<std::underlying_type_t<Ty>>(enumElem);
}

} /* namespace tgon */