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

template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType = StringTraits<_CharType>>
constexpr auto MakeFixedString(const _CharType(&str)[_CharArraySize]) -> BasicFixedString<typename std::decay<_CharType>::type, _CharArraySize, _StringTraitsType>
{
    return {str, _CharArraySize - 1};
}

} /* namespace string */
} /* namespace tgon */
