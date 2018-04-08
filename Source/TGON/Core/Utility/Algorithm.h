/**
 * @filename    Algorithm.h
 * @author      ggomdyu
 * @since       07/05/2016
 * @brief       Utility support for algorithm.
 */

#pragma once
#include <cstddef>
#include <tuple>

namespace tgon
{

template <typename _CharType>
constexpr bool IsPalindrome(const _CharType* str, std::size_t length)
{
    std::size_t halfStrLength = length / 2;

    for (std::size_t i = 0; i < halfStrLength; ++i)
    {
        if (str[i] != str[length - i])
        {
            return false;
        }
    }
    return true;
}

template <std::size_t _Index = 0,  typename _CallbackType, typename... _ArgTypes>
inline typename std::enable_if<_Index == sizeof...(_ArgTypes)>::type ForEach(std::tuple<_ArgTypes...>& tuple, const _CallbackType& callback) noexcept
{
}

template <std::size_t _Index = 0,  typename _CallbackType, typename... _ArgTypes>
inline typename std::enable_if<_Index < sizeof...(_ArgTypes)>::type ForEach(std::tuple<_ArgTypes...>& tuple, const _CallbackType& callback) noexcept
{
    callback(std::get<_Index>(tuple));
    ForEach<_Index + 1, _CallbackType, _ArgTypes...>(tuple, callback);
}

template <typename... _ArgTypes, typename _CallbackType>
inline void ForEach(std::pair<_ArgTypes...>& pair, const _CallbackType& callback)
{
    callback(pair.first);
    callback(pair.second);
}

template <typename _IteratorType, typename _CallbackType>
inline void ForEach(_IteratorType beginIter, _IteratorType endIter, const _CallbackType& callback)
{
    while (beginIter != endIter)
    {
        callback(*beginIter);

        ++beginIter;
    }
}

template <typename _ContainerType, typename _CallbackType>
inline void ForEach(_ContainerType& container, const _CallbackType& callback)
{
    ForEach(container.begin(), container.end(), callback);
}

template <typename _ContainerType, typename _CallbackType>
inline void ForEach(const _ContainerType& container, const _CallbackType& callback)
{
    ForEach(container.cbegin(), container.cend(), callback);
}

template <typename _ContainerType, typename _PredicateType>
inline void EraseAll(_ContainerType& container, const _PredicateType& predicate)
{
    for (auto iter = container.begin(); iter != container.end();)
    {
        if (predicate(*iter) == true)
        {
            iter = container.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

template <typename _ContainerType, typename _PredicateType, typename _CallbackType>
inline void FindAll(_ContainerType& container, const _PredicateType& predicate, const _CallbackType& callback)
{
    for (auto iter = container.begin(); iter != container.end(); ++iter)
    {
        if (predicate(*iter) == true)
        {
            callback(*iter);
        }
    }
}

template <typename _ArrayElementType, std::size_t _ArraySize>
constexpr std::size_t GetArraySize(const _ArrayElementType(&)[_ArraySize]) noexcept
{
    return _ArraySize;
}

template <typename _EnumType>
constexpr std::underlying_type_t<_EnumType> UnderlyingCast(_EnumType value) noexcept
{
    return static_cast<std::underlying_type_t<_EnumType>>(value);
}

template <typename _Type>
void Swap(_Type& lhs, _Type& rhs) noexcept(std::is_nothrow_move_constructible_v<_Type> && std::is_nothrow_move_assignable_v<_Type>)
{
    _Type temp = std::move(lhs);
    lhs = std::move(rhs);
    rhs = std::move(temp);
}

} /* namespace tgon */
