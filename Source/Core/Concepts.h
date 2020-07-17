#pragma once

#include <type_traits>
#include <concepts>

namespace tg
{

template <typename _Type>
concept Arithmetic = std::is_arithmetic_v<_Type>;

template <typename _Type>
concept Hashable = requires(_Type value)
{
    { std::hash<_Type>{}(value) } -> std::convertible_to<size_t>;
};

template <typename _Type>
concept Indexable = requires(_Type value) { value[0]; };

template <typename _Type>
concept Cloneable = requires(_Type* value) { value->Clone(); };

}
