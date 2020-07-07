#pragma once

#include <type_traits>
#include <concepts>

namespace tg
{

template <typename _Type>
concept Arithmetic = std::is_arithmetic_v<_Type>;

template <typename _Type>
concept Hashable = requires {
    std::hash<_Type>{}();
};

}
