/**
 * @file    Span.h
 * @author  ggomdyu
 * @since   08/07/2019
 */

#pragma once
#include <cstdint>
#include <array>
#include <cassert>
#include <numeric>

namespace tgon
{
namespace detail
{

/**@brief   DynamicExtent is used to differentiate Span of static or dynamic extent. */
constexpr auto DynamicExtent = std::numeric_limits<int32_t>::max();

template <typename _ElementType, std::size_t N>
class SpanStorage
{
/**@section Constructor */
public:
    constexpr SpanStorage() noexcept;
    constexpr SpanStorage(_ElementType* data, int32_t) noexcept;

/**@section Variable */
protected:
    _ElementType* m_data;
    static constexpr int32_t m_size = static_cast<int32_t>(N);
};

template <typename _ElementType, std::size_t N>
constexpr SpanStorage<_ElementType, N>::SpanStorage() noexcept :
    m_data(nullptr)
{
}

template <typename _ElementType, std::size_t N>
constexpr SpanStorage<_ElementType, N>::SpanStorage(_ElementType* data, int32_t) noexcept :
    m_data(data)
{
}

template <typename _ElementType>
class SpanStorage<_ElementType, DynamicExtent>
{
/**@section Constructor */
public:
    constexpr SpanStorage() noexcept;
    constexpr SpanStorage(_ElementType* data, int32_t size) noexcept;

/**@section Variable */
protected:
    _ElementType* m_data;
    int32_t m_size;
};

template <typename _ElementType>
constexpr SpanStorage<_ElementType, DynamicExtent>::SpanStorage() noexcept :
    m_data(nullptr),
    m_size(0)
{
}

template <typename _ElementType>
constexpr SpanStorage<_ElementType, DynamicExtent>::SpanStorage(_ElementType* data, int32_t size) noexcept :
    m_data(data),
    m_size(static_cast<int32_t>(size))
{
}

} /* namespace detail */

template <typename _ElementType, std::size_t N = detail::DynamicExtent>
class Span final :
    private detail::SpanStorage<_ElementType, N>
{
/**@section Type */
public:
    using ElementType = _ElementType;
    using PointerType = _ElementType*;
    using ConstointerType = const _ElementType*;
    using ReferenceType = _ElementType&;
    using ConstReferenceType = const _ElementType&;

private:
    using SpanStorageType = detail::SpanStorage<_ElementType, N>;

    template <int32_t Start, int32_t Length>
    using SubSpanType = Span<_ElementType, (N != detail::DynamicExtent) ? Length - Start : detail::DynamicExtent>;
    
/**@section Constructor */
public:
    constexpr Span(PointerType ptr, int32_t count) noexcept;
    constexpr Span(_ElementType(&arr)[N]) noexcept;
    
/**@section Operator */
public:
    constexpr ReferenceType operator[](int32_t index);
    constexpr ConstReferenceType operator[](int32_t index) const;
    
/**@section Method */
public:
    constexpr bool IsEmpty() const noexcept;
    constexpr int32_t Length() const noexcept;
    constexpr Span<_ElementType> Slice(int32_t start) const;
    constexpr Span<_ElementType> Slice(int32_t start, int32_t length) const;
    template <int32_t Start, int32_t Length = detail::DynamicExtent>
    constexpr SubSpanType<Start, Length> Slice() const noexcept
    {
        return {};
    }
    void Clear();
    void Fill(const _ElementType& value);
};

template <typename _ElementType, std::size_t N>
Span(_ElementType(&)[N]) -> Span<_ElementType, N>;

template <typename _ElementType, std::size_t N>
Span(const _ElementType(&)[N]) -> Span<const _ElementType, N>;

template <typename _ElementType>
Span(_ElementType*, int32_t) -> Span<_ElementType>;

template <typename _ElementType>
Span(const _ElementType*, int32_t) -> Span<const _ElementType>;

//template <typename _ContainerType, std::size_t N>
//Span(_ContainerType&) -> Span<typename _ContainerType::value_type, N>;
//
//template <typename _ContainerType, std::size_t N>
//Span(const _ContainerType&)->Span<const typename _ContainerType::value_type, N>;

template <typename _ContainerType>
Span(_ContainerType&) -> Span<typename _ContainerType::value_type>;

template <typename _ContainerType>
Span(const _ContainerType&) -> Span<const typename _ContainerType::value_type>;

template <typename>
struct IsSpan : std::false_type {};

template <typename _ElementType, std::size_t N>
struct IsSpan<Span<_ElementType, N>> : std::true_type {};

template <typename _ElementType, std::size_t N>
constexpr bool IsSpanValue = IsSpan<_ElementType, N>::value;

template <typename _ElementType, std::size_t N>
constexpr Span<_ElementType, N>::Span(PointerType ptr, int32_t count) noexcept :
    SpanStorageType(str, count)
{
}

template <typename _ElementType, std::size_t N>
constexpr Span<_ElementType, N>::Span(_ElementType(&arr)[N]) noexcept :
    SpanStorageType(arr, N)
{
}

template <typename _ElementType, std::size_t N>
constexpr typename Span<_ElementType, N>::ReferenceType Span<_ElementType, N>::operator[](int32_t index)
{
    assert(index >= 0 && index < m_size);
    return m_data[index];
}

template <typename _ElementType, std::size_t N>
constexpr typename Span<_ElementType, N>::ConstReferenceType Span<_ElementType, N>::operator[](int32_t index) const
{
    return const_cast<decltype(this)>->operator[](index);
}

template <typename _ElementType, std::size_t N>
constexpr bool Span<_ElementType, N>::IsEmpty() const noexcept
{
    return m_size == 0;
}

template <typename _ElementType, std::size_t N>
constexpr int32_t Span<_ElementType, N>::Length() const noexcept
{
    return m_size;
}

template<typename _ElementType, std::size_t N>
constexpr Span<_ElementType> Span<_ElementType, N>::Slice(int32_t start) const
{
    assert(start >= 0 && start <= m_size);
    return {m_data + start, m_size - start};
}

template<typename _ElementType, std::size_t N>
constexpr Span<_ElementType> Span<_ElementType, N>::Slice(int32_t start, int32_t length) const
{
    assert((start >= 0 && start <= length) && (length >= 0 && start + length <= m_size));
    return {m_data + start, length};
}

template<typename _ElementType, std::size_t N>
inline void Span<_ElementType, N>::Clear()
{
    for (std::size_t i = 0; i < m_size; ++i)
    {
        m_data[i] = {};
    }
}

template <typename _ElementType, std::size_t N>
inline void Span<_ElementType, N>::Fill(const _ElementType& value)
{
    for (std::size_t i = 0; i < m_size; ++i)
    {
        m_data[i] = value;
    }
}

} /* namespace tgon */