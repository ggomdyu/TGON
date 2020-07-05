#pragma once

#include <cstddef>
#include <tuple>
#include <type_traits>
#include <array>
#include <algorithm>

namespace tg
{

template <typename _Value>
constexpr _Value AlignOf(const _Value& value, size_t alignment)
{
    return (value + alignment - 1) & ~(alignment - 1);
}

template <typename _Char>
constexpr bool IsPalindrome(const _Char* str, size_t strLen)
{
    for (size_t i = 0; i < strLen / 2; ++i)
    {
        if (str[i] != str[strLen - i])
        {
            return false;
        }
    }
    return true;
}

template <size_t _TupleIndex = 0, typename _Callback, typename... _Args> requires (_TupleIndex == sizeof...(_Args))
void ForEach(std::tuple<_Args...>& tuple, const _Callback& callback) noexcept
{
}

template <size_t _TupleIndex = 0, typename _Callback, typename... _Args> requires (_TupleIndex < sizeof...(_Args))
void ForEach(std::tuple<_Args...>& tuple, const _Callback& callback) noexcept
{
    callback(std::get<_TupleIndex>(tuple));
    ForEach<_TupleIndex + 1, _Callback, _Args...>(tuple, callback);
}

template <typename... _Args, typename _Callback>
void ForEach(std::pair<_Args...>& pair, const _Callback& callback)
{
    callback(pair.first);
    callback(pair.second);
}

template <typename _Iter, typename _Callback>
void ForEach(_Iter beginIter, _Iter endIter, const _Callback& callback)
{
    while (beginIter != endIter)
    {
        callback(*beginIter);

        ++beginIter;
    }
}

template <typename _Container, typename _Callback>
void ForEach(_Container& container, const _Callback& callback)
{
    ForEach(container.begin(), container.end(), callback);
}

template <typename _Container, typename _Callback>
void ForEach(const _Container& container, const _Callback& callback)
{
    ForEach(container.cbegin(), container.cend(), callback);
}

template <typename _Container, typename _Predicate>
void EraseAll(_Container& container, const _Predicate& predicate)
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

template <typename _Container, typename _Predicate, typename _Callback>
void FindAll(_Container& container, const _Predicate& predicate, const _Callback& callback)
{
    for (auto iter = container.begin(); iter != container.end(); ++iter)
    {
        if (predicate(*iter) == true)
        {
            callback(*iter);
        }
    }
}

template <typename _ArrayElem, size_t _ArraySize>
constexpr size_t GetArraySize(const _ArrayElem(&)[_ArraySize]) noexcept
{
    return _ArraySize;
}

template <typename... _Args>
constexpr std::array<std::decay_t<std::common_type_t<_Args...>>, sizeof...(_Args)> MakeArray(_Args&&... rhs) noexcept
{
    return {std::forward<_Args>(rhs)...};
}

template <typename _Enum> requires std::is_enum_v<_Enum>
constexpr std::underlying_type_t<_Enum> UnderlyingCast(_Enum value) noexcept
{
    return static_cast<std::underlying_type_t<_Enum>>(value);
}

template <typename _Type>
void Swap(_Type& lhs, _Type& rhs) noexcept(std::is_nothrow_move_constructible<_Type>::value && std::is_nothrow_move_assignable<_Type>::value)
{
    _Type temp = std::move(lhs);
    lhs = std::move(rhs);
    rhs = std::move(temp);
}

template <typename _Iter, typename _Value>
bool BinarySearch(_Iter begin, _Iter end, const _Value& value)
{
    begin = std::lower_bound(begin, end, value);
    return !(begin == end) && !(value < *begin);
}

template <typename _Iter, typename _Value, typename _Predicate>
bool BinarySearch(_Iter begin, _Iter end, const _Value& value, _Predicate predicate)
{
    begin = std::lower_bound(begin, end, value, predicate);
    return !(begin == end) && !predicate(*begin, value);
}

}
