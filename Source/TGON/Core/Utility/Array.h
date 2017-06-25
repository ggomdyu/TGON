/**
 * @filename    Array.h
 * @author      ggomdyu
 * @since       06/20/2016
 */

#pragma once
#include <cstddef>

namespace tgon
{
namespace utility
{

template <typename ArrayTy, std::size_t ArrayLength>
constexpr std::size_t GetArraySize(const ArrayTy(&)[ArrayLength]) noexcept
{
	return ArrayLength;
}

} /* namespace utility */
} /* namespace tgon */
