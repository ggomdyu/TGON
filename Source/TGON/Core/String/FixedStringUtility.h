/**
 * @filename    FixedStringUtil.h
 * @author      ggomdyu
 * @date        03/16/2017
 */

#pragma once
#include <cstdint>
#include <type_traits>

#include "FixedString.h"

namespace tgon
{
namespace string
{

template <typename CharTy, std::size_t N>
constexpr auto MakeFixedString(CharTy(&str)[N]) -> BasicFixedString<typename std::remove_const<CharTy>::type, N>
{
    return {str, N - 1};
}

} /* namespace string */
} /* namespace tgon */
