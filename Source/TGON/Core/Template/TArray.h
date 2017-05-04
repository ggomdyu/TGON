/**
 * @filename    TArray.h
 * @author   ggomdyu
 * since    06/20/2016
 */

#pragma once
#include <cstddef>

namespace tgon
{

template <typename Ty, std::size_t N>
constexpr std::size_t GetArraySize(Ty(&)[N]) noexcept
{
	return N;
}

} /* namespace tgon */
