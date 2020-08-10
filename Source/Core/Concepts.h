#pragma once

#include "TypeTraits.h"

namespace tg
{

template <typename _Type>
concept Arithmetic = std::is_arithmetic_v<_Type>;

template <typename _Type>
concept FloatingPoint = std::is_floating_point_v<_Type>;

template <typename _Type>
concept Integral = std::is_integral_v<_Type>;

template <typename _From, typename _To>
concept ConvertibleTo = std::is_convertible<_From, _To>::value;

template <typename _Type>
concept Hashable = IsHashable<_Type>;

template <typename _Type>
concept Indexable = IsIndexable<_Type>;

}