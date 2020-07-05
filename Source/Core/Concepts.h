#pragma once

#include <type_traits>
#include <concepts>

namespace tg
{

template <typename _Type>
concept IsArithmetic = std::is_arithmetic_v<_Type>;

}
