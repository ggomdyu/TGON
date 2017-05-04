/**
 * @filename    TFixedStringUtil.h
 * @author      ggomdyu
 * @date        03/16/2017
 */

#pragma once
#include <cstdint>
#include <type_traits>

#include "TFixedString.h"

namespace tgon {
namespace string {

template <typename CharTy, std::size_t N>
inline constexpr auto MakeFixedString(CharTy(&str)[N]) -> TBasicFixedString<std::remove_const_t<CharTy>, N>
{
    return {str, N - 1};
}

} /* namespace string */
} /* namespace tgon */