/**
 * @file    Range.h
 * @author  ggomdyu
 * @since   07/06/2019
 */

#pragma once
#include <iterator>

namespace tgon
{

template <typename _ValueType>
class Range
{
/**@section Type */
public:
    using Iterator = _ValueType*;
    using ConstIterator = const _ValueType*;
    using ReverseIterator = std::reverse_iterator<Iterator>;
    using ConstReverseIterator = std::reverse_iterator<ConstIterator>;
    
/**@section Constructor */
public:
    Range(Iterator begin, Iterator end) noexcept;
    
/**@section Method */
public:
    Iterator begin() noexcept;
    Iterator end() noexcept;
    ConstIterator begin() const noexcept;
    ConstIterator end() const noexcept;
    ReverseIterator rbegin() noexcept;
    ReverseIterator rend() noexcept;
    ConstReverseIterator rbegin() const noexcept;
    ConstReverseIterator rend() const noexcept;
    
/**@section Variable */
private:
    Iterator m_begin;
    Iterator m_end;
};

template <typename _ValueType>
inline Range<_ValueType>::Range(Iterator begin, Iterator end) noexcept :
    m_begin(begin),
    m_end(end)
{
}

template <typename _ValueType>
inline typename Range<_ValueType>::Iterator Range<_ValueType>::begin() noexcept
{
    return m_begin;
}

template <typename _ValueType>
inline typename Range<_ValueType>::Iterator Range<_ValueType>::end() noexcept
{
    return m_end;
}

template <typename _ValueType>
inline typename Range<_ValueType>::ConstIterator Range<_ValueType>::begin() const noexcept
{
    return m_begin;
}

template <typename _ValueType>
inline typename Range<_ValueType>::ConstIterator Range<_ValueType>::end() const noexcept
{
    return m_end;
}

template <typename _ValueType>
inline typename Range<_ValueType>::ReverseIterator Range<_ValueType>::rbegin() noexcept
{
    return m_end;
}

template <typename _ValueType>
inline typename Range<_ValueType>::ReverseIterator Range<_ValueType>::rend() noexcept
{
    return m_begin;
}

template <typename _ValueType>
inline typename Range<_ValueType>::ConstReverseIterator Range<_ValueType>::rbegin() const noexcept
{
    return m_end;
}

template <typename _ValueType>
inline typename Range<_ValueType>::ConstReverseIterator Range<_ValueType>::rend() const noexcept
{
    return m_begin;
}

} /* namespace tgon */
