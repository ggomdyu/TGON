/**
* @filename    Conditional.h
* @author      ggomdyu
* @since       07/01/2017
*/

#pragma once

#include <type_traits>

namespace tgon
{
namespace utility
{
namespace detail
{

enum StaticIfCondition
{
    kFalse = 0,
    kTrue = 1,
    kConditional = 2,
};

template <int Condition>
struct StaticIfProxy;

template <>
struct StaticIfProxy<2>
{
public:
    template <typename FunctionTy>
    const StaticIfProxy<2> StaticThen(FunctionTy&& function)
    {
    };

    template <int Condition2, typename FunctionTy>
    const StaticIfProxy<2> StaticElseIf(FunctionTy&& function)
    {
    };

    template <typename FunctionTy>
    void StaticElse(FunctionTy&& function) const noexcept
    {
    };
};

template <>
struct StaticIfProxy<1>
{
public:
    template <typename FunctionTy>
    const StaticIfProxy<2> StaticThen(FunctionTy&& function) const;

    template <int Condition2, typename FunctionTy>
    const StaticIfProxy<2> StaticElseIf(FunctionTy&& function) const;

    template <typename FunctionTy>
    void StaticElse(FunctionTy&& function) const noexcept;
};

template <typename FunctionTy>
inline const StaticIfProxy<2> StaticIfProxy<1>::StaticThen(FunctionTy&& function) const
{
    function();
    return StaticIfProxy<2>{};
}

template <>
struct StaticIfProxy<0>
{
public:
    template <typename FunctionTy>
    constexpr const StaticIfProxy<0> StaticThen(FunctionTy&& function) const noexcept;

    template <int Condition2, typename FunctionTy>
    const StaticIfProxy<Condition2 == 1 ? 2 : 0> StaticElseIf(FunctionTy&& function) const;

    template <typename FunctionTy>
    void StaticElse(FunctionTy&& function) const;
};

template <int Condition2, typename FunctionTy>
inline const StaticIfProxy<2> StaticIfProxy<1>::StaticElseIf(FunctionTy&& function) const
{
    return {};
}

template <typename FunctionTy>
void StaticIfProxy<1>::StaticElse(FunctionTy&& function) const noexcept
{
}

template <typename FunctionTy>
constexpr const StaticIfProxy<0> StaticIfProxy<0>::StaticThen(FunctionTy&& function) const noexcept
{
    return {};
}

template <int Condition2, typename FunctionTy>
const StaticIfProxy<Condition2 == 1 ? 2 : 0> StaticIfProxy<0>::StaticElseIf(FunctionTy&& function) const
{
    StaticIfProxy<Condition2>{}.StaticThen(function);
    return {};
}

template <typename FunctionTy>
inline void StaticIfProxy<0>::StaticElse(FunctionTy&& function) const
{
    function();
}

} /* namespace detail */

template <int Condition, typename FunctionTy>
detail::StaticIfProxy<Condition> StaticIf(FunctionTy&& function)
{
    detail::StaticIfProxy<Condition>{}.StaticThen(function);
    return {};
}

} /* namespace utility */
} /* namespace tgon */
