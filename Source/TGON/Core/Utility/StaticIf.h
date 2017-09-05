/**
 * @filename    StaticIf.h
 * @author      ggomdyu
 * @since       07/01/2017
 * @brief       static-if implementation for C++11/14.
 * @seealso     https://github.com/CppCon/CppCon2016/blob/master/Tutorials/Implementing%20static%20control%20flow%20in%20C%2B%2B14/Implementing%20static%20control%20flow%20in%20C%2B%2B14%20-%20Vittorio%20Romeo%20-%20CppCon%202016.pdf
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

template <StaticIfCondition _Condition>
struct StaticIfProxy;

template <>
struct StaticIfProxy<StaticIfCondition::kEndOfContext>
{
public:
    template <typename _FunctionType>
    constexpr const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticThen(_FunctionType&& function) const noexcept;

    template <int32_t _Condition, typename _FunctionType>
    constexpr const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticElseIf(_FunctionType&& function) const noexcept;

    template <typename _FunctionType>
    void StaticElse(_FunctionType&& function) const noexcept;
};

template <typename _FunctionType>
constexpr const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticIfProxy<StaticIfCondition::kEndOfContext>::StaticThen(_FunctionType&& function) const noexcept
{
    return {};
};

template <int32_t _Condition, typename _FunctionType>
constexpr const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticIfProxy<StaticIfCondition::kEndOfContext>::StaticElseIf(_FunctionType&& function) const noexcept
{
    return {};
};

template <typename _FunctionType>
inline void StaticIfProxy<StaticIfCondition::kEndOfContext>::StaticElse(_FunctionType&& function) const noexcept
{
};

template <>
struct StaticIfProxy<StaticIfCondition::kTrue>
{
public:
    template <typename _FunctionType>
    const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticThen(_FunctionType&& function) const;

    template <int32_t _Condition, typename _FunctionType>
    const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticElseIf(_FunctionType&& function) const;

    template <typename _FunctionType>
    void StaticElse(_FunctionType&& function) const noexcept;
};

template <typename _FunctionType>
inline const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticIfProxy<StaticIfCondition::kTrue>::StaticThen(_FunctionType&& function) const
{
    function();
    return StaticIfProxy<StaticIfCondition::kEndOfContext>{};
}

template <>
struct StaticIfProxy<StaticIfCondition::kFalse>
{
public:
    template <typename _FunctionType>
    constexpr const StaticIfProxy<StaticIfCondition::kFalse> StaticThen(_FunctionType&& function) const noexcept;

    template <int32_t _Condition, typename _FunctionType>
    const StaticIfProxy<static_cast<StaticIfCondition>(_Condition) == StaticIfCondition::kTrue ? StaticIfCondition::kEndOfContext : StaticIfCondition::kFalse> StaticElseIf(_FunctionType&& function) const;

    template <typename _FunctionType>
    void StaticElse(_FunctionType&& function) const;
};

template <int32_t _Condition, typename _FunctionType>
inline const StaticIfProxy<StaticIfCondition::kEndOfContext> StaticIfProxy<StaticIfCondition::kTrue>::StaticElseIf(_FunctionType&& function) const
{
    return {};
}

template <typename _FunctionType>
inline void StaticIfProxy<StaticIfCondition::kTrue>::StaticElse(_FunctionType&& function) const noexcept
{
}

template <typename _FunctionType>
constexpr const StaticIfProxy<StaticIfCondition::kFalse> StaticIfProxy<StaticIfCondition::kFalse>::StaticThen(_FunctionType&& function) const noexcept
{
    return {};
}

template <int32_t _Condition, typename _FunctionType>
const StaticIfProxy<static_cast<StaticIfCondition>(_Condition) == StaticIfCondition::kTrue ? StaticIfCondition::kEndOfContext : StaticIfCondition::kFalse> StaticIfProxy<StaticIfCondition::kFalse>::StaticElseIf(_FunctionType&& function) const
{
    StaticIfProxy<static_cast<StaticIfCondition>(_Condition)>{}.StaticThen(std::forward<_FunctionType>(function));
    return {};
}

template <typename _FunctionType>
inline void StaticIfProxy<StaticIfCondition::kFalse>::StaticElse(_FunctionType&& function) const
{
    function();
}

} /* namespace detail */

template <int32_t _Condition, typename _FunctionType>
constexpr detail::StaticIfProxy<static_cast<detail::StaticIfCondition>(_Condition)> StaticIf(_FunctionType&& function)
{
    detail::StaticIfProxy<static_cast<detail::StaticIfCondition>(_Condition)>{}.StaticThen(std::forward<_FunctionType>(function));
    return {};
}

} /* namespace utility */
} /* namespace tgon */
