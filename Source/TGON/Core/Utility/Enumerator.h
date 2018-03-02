/**
 * @filename    Enumerator.h
 * @author      ggomdyu
 * @since       06/20/2016
 */

#pragma once
#include <type_traits>

namespace tgon
{
namespace core
{

template <typename _EnumType>
constexpr typename std::underlying_type<_EnumType>::type ToUnderlying(_EnumType value) noexcept
{
    return static_cast<typename std::underlying_type<_EnumType>::type>(value);
}

} /* namespace core */
} /* namespace tgon */