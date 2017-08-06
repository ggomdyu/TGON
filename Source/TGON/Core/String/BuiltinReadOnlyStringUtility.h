/**
 * @filename    BuiltinReadOnlyStringUtility.h
 * @author      ggomdyu
 * @date        08/06/2017
 */

#pragma once
#include "Core/String/BuiltinReadOnlyString.h"

namespace tgon
{
namespace string
{

template <typename _CharType, std::size_t _CharArraySize>
constexpr const BuiltinReadOnlyString<const typename std::decay<_CharType>::type, _CharArraySize> MakeBuiltinReadOnlyString(const _CharType(&str)[_CharArraySize])
{
    return {str};
}

} /* namespace string */
} /* namespace tgon */