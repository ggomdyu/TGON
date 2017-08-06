/**
 * @filename    FixedStringUtility.h
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

template <typename _CharType, std::size_t _BufferSize>
constexpr BasicFixedString<typename std::decay<_CharType>::type, _BufferSize> MakeFixedString(const _CharType(&str)[_BufferSize])
{
    return {str, _BufferSize - 1};
}

} /* namespace string */
} /* namespace tgon */
