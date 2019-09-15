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
    using IteratorType = _ValueType*;
    using ConstIteratorType = const _ValueType*;
    using ReverseIteratorType = std::reverse_iterator<IteratorType>;
    using ConstReverseIteratorType = std::reverse_iterator<ConstIteratorType>;
    
/**@section Constructor */
public:
    Range(IteratorType begin, IteratorType end) noexcept;
    
/**@section Method */
public:
    IteratorType begin() noexcept;
    IteratorType end() noexcept;
    ConstIteratorType begin() const noexcept;
    ConstIteratorType end() const noexcept;
    ReverseIteratorType rbegin() noexcept;
    ReverseIteratorType rend() noexcept;
    ConstReverseIteratorType rbegin() const noexcept;
    ConstReverseIteratorType rend() const noexcept;
    
/**@section Variable */
private:
    IteratorType m_begin;
    IteratorType m_end;
};

template <typename _ValueType>
Range(typename Range<_ValueType>::IteratorType first, typename Range<_ValueType>::IteratorType second) -> Range<_ValueType>;

template <typename _ValueType>
inline Range<_ValueType>::Range(IteratorType begin, IteratorType end) noexcept :
    m_begin(begin),
    m_end(end)
{
}

template <typename _ValueType>
inline typename Range<_ValueType>::IteratorType Range<_ValueType>::begin() noexcept
{
    return m_begin;
}

template <typename _ValueType>
inline typename Range<_ValueType>::IteratorType Range<_ValueType>::end() noexcept
{
    return m_end;
}

template <typename _ValueType>
inline typename Range<_ValueType>::ConstIteratorType Range<_ValueType>::begin() const noexcept
{
    return m_begin;
}

template <typename _ValueType>
inline typename Range<_ValueType>::ConstIteratorType Range<_ValueType>::end() const noexcept
{
    return m_end;
}

template <typename _ValueType>
inline typename Range<_ValueType>::ReverseIteratorType Range<_ValueType>::rbegin() noexcept
{
    return m_end;
}

template <typename _ValueType>
inline typename Range<_ValueType>::ReverseIteratorType Range<_ValueType>::rend() noexcept
{
    return m_begin;
}

template <typename _ValueType>
inline typename Range<_ValueType>::ConstReverseIteratorType Range<_ValueType>::rbegin() const noexcept
{
    return m_end;
}

template <typename _ValueType>
inline typename Range<_ValueType>::ConstReverseIteratorType Range<_ValueType>::rend() const noexcept
{
    return m_begin;
}

} /* namespace tgon */
