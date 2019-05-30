/**
 * @file    FixedStringUtility.h
 * @author  ggomdyu
 * @date    03/16/2017
 */

#pragma once
#include "FixedString.h"

namespace tgon
{
    
template <typename _CharType, std::size_t _CharArraySize, typename _StringTraitsType = BasicStringTraits<_CharType>>
constexpr auto MakeFixedString(const _CharType(&str)[_CharArraySize]) -> BasicFixedString<_CharType, _CharArraySize, _StringTraitsType>
{
    return MakeFixedString(str, _CharArraySize - 1);
}

} /* namespace tgon */
