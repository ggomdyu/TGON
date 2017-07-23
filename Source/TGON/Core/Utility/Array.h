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

template <typename _ArrayType, std::size_t _ArraySize>
constexpr std::size_t GetArraySize(const _ArrayType(&)[_ArraySize]) noexcept
{
	return _ArraySize;
}

} /* namespace utility */
} /* namespace tgon */
