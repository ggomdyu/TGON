/**
 * @filename    Enumerator.h
 * @author      ggomdyu
 * @since       06/20/2016
 */

#pragma once
#include <type_traits>

namespace tgon
{
namespace utility
{

template <typename _EnumType>
constexpr typename std::underlying_type<_EnumType>::type Underlying(_EnumType value)
{
    return static_cast<typename std::underlying_type<_EnumType>::type>(value);
}

} /* namespace utility */
} /* namespace tgon */
