/**
* @filename    Conditional.h
* @author      ggomdyu
* @since       07/01/2017
*/

#pragma once

namespace tgon
{
namespace utility
{
namespace detail
{

enum class StaticIfCondition
{
    kFalse = 0,
    kTrue = 1,
    kEndOfContext = 2,
};

template <StaticIfCondition Condition>
struct StaticIfProxy;

template <>
struct StaticIfProxy<StaticIfCondition::kEndOfContext>
{
public:
    template <typename FunctionTy>
    constexpr const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticThen(FunctionTy&& function) const noexcept;

    template <int Condition, typename FunctionTy>
    constexpr const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticElseIf(FunctionTy&& function) const noexcept;

    template <typename FunctionTy>
    void StaticElse(FunctionTy&& function) const noexcept;
};

template <typename FunctionTy>
constexpr const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticIfProxy<StaticIfCondition::kEndOfContext>::StaticThen(FunctionTy&& function) const noexcept
{
    return {};
};

template <int Condition, typename FunctionTy>
constexpr const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticIfProxy<StaticIfCondition::kEndOfContext>::StaticElseIf(FunctionTy&& function) const noexcept
{
    return {};
};

template <typename FunctionTy>
inline void StaticIfProxy<StaticIfCondition::kEndOfContext>::StaticElse(FunctionTy&& function) const noexcept
{
};

template <>
struct StaticIfProxy<StaticIfCondition::kTrue>
{
public:
    template <typename FunctionTy>
    const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticThen(FunctionTy&& function) const;

    template <int Condition, typename FunctionTy>
    const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticElseIf(FunctionTy&& function) const;

    template <typename FunctionTy>
    void StaticElse(FunctionTy&& function) const noexcept;
};

template <typename FunctionTy>
inline const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticIfProxy<StaticIfCondition::kTrue>::StaticThen(FunctionTy&& function) const
{
    function();
    return StaticIfProxy<StaticIfCondition::kEndOfContext>{};
}

template <>
struct StaticIfProxy<StaticIfCondition::kFalse>
{
public:
    template <typename FunctionTy>
    constexpr const StaticIfProxy<StaticIfCondition::kFalse> StaticThen(FunctionTy&& function) const noexcept;

    template <int Condition, typename FunctionTy>
    const StaticIfProxy<static_cast<StaticIfCondition>(Condition) == StaticIfCondition::kTrue ? StaticIfCondition::kEndOfContext : StaticIfCondition::kFalse> StaticElseIf(FunctionTy&& function) const;

    template <typename FunctionTy>
    void StaticElse(FunctionTy&& function) const;
};

template <int Condition, typename FunctionTy>
inline const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticIfProxy<StaticIfCondition::kTrue>::StaticElseIf(FunctionTy&& function) const
{
    return {};
}

template <typename FunctionTy>
inline void StaticIfProxy<StaticIfCondition::kTrue>::StaticElse(FunctionTy&& function) const noexcept
{
}

template <typename FunctionTy>
constexpr const StaticIfProxy<StaticIfCondition::kFalse> StaticIfProxy<StaticIfCondition::kFalse>::StaticThen(FunctionTy&& function) const noexcept
{
    return {};
}

template <int Condition, typename FunctionTy>
const StaticIfProxy<static_cast<StaticIfCondition>(Condition) == StaticIfCondition::kTrue ? StaticIfCondition::kEndOfContext : StaticIfCondition::kFalse> StaticIfProxy<StaticIfCondition::kFalse>::StaticElseIf(FunctionTy&& function) const
{
    StaticIfProxy<static_cast<StaticIfCondition>(Condition)>{}.StaticThen(function);
    return {};
}

template <typename FunctionTy>
inline void StaticIfProxy<StaticIfCondition::kFalse>::StaticElse(FunctionTy&& function) const
{
    function();
}

} /* namespace detail */

template <int Condition, typename FunctionTy>
constexpr detail::StaticIfProxy<static_cast<detail::StaticIfCondition>(Condition)> StaticIf(FunctionTy&& function)
{
    detail::StaticIfProxy<static_cast<detail::StaticIfCondition>(Condition)>{}.StaticThen(function);
    return {};
}

} /* namespace utility */
} /* namespace tgon */
