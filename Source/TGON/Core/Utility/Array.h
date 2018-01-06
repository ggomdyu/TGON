/**
 * @filename    Array.h
 * @author      ggomdyu
 * @since       06/20/2016
 */

#pragma once
#include <cstddef>

namespace tgon
{
namespace core
{

template <typename _ArrayElementType, std::size_t _ArraySize>
constexpr std::size_t GetArraySize(const _ArrayElementType(&)[_ArraySize]) noexcept
{
	return _ArraySize;
}

} /* namespace core */
} /* namespace tgon */
