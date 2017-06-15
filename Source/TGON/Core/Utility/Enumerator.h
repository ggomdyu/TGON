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

template <typename EnumTy>
constexpr typename std::underlying_type<EnumTy>::type Underlying(EnumTy value)
{
    return static_cast<typename std::underlying_type<EnumTy>::type>(value);
}

} /* namespace utility */
} /* namespace tgon */
