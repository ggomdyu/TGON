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

#if defined(_DEBUG) || defined(NDEBUG)
#   define TGON_STRINGIFY(m) #m
#   define TGON_EXPECT(e)\
if (!e)\
{\
    throw std::logic_error("Span expected:" TGON_STRINGIFY(e));\
}
#else
#   define TGON_EXPECT(e)
#endif

namespace tgon
{
namespace detail
{

/**@brief   DynamicExtent is used to differentiate Span of static or dynamic extent. */
constexpr int32_t DynamicExtent = std::numeric_limits<int32_t>::max();

template <typename _ElementType, int32_t Extent>
class SpanStorage
{
/**@section Constructor */
public:
    constexpr SpanStorage() noexcept;
    constexpr SpanStorage(_ElementType* data, int32_t) noexcept;

/**@section Variable */
protected:
    _ElementType* m_data;
    static constexpr int32_t m_size = Extent;
};

template <typename _ElementType, int32_t Extent>
constexpr SpanStorage<_ElementType, Extent>::SpanStorage() noexcept :
    m_data(nullptr)
{
}

template <typename _ElementType, int32_t Extent>
constexpr SpanStorage<_ElementType, Extent>::SpanStorage(_ElementType* data, int32_t) noexcept :
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

template <typename _ElementType, int32_t Extent = detail::DynamicExtent>
class Span final :
    private detail::SpanStorage<_ElementType, Extent>
{
/**@section Type */
public:
    using ElementType = _ElementType;
    using PointerType = _ElementType*;
    using ConstointerType = const _ElementType*;
    using ReferenceType = _ElementType&;
    using ConstReferenceType = const _ElementType&;

private:
    using SpanStorageType = detail::SpanStorage<_ElementType, Extent>;

    template <int32_t Start, int32_t Length>
    using SubSpanType = Span<_ElementType, (Length != detail::DynamicExtent) ? Length : (Extent != detail::DynamicExtent) ? Extent - Start : detail::DynamicExtent>;
    
/**@section Constructor */
public:
    constexpr Span(PointerType ptr, int32_t count) noexcept;
    constexpr Span(_ElementType(&arr)[Extent]) noexcept;
    
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
    constexpr SubSpanType<Start, Length> Slice() const;
    void Clear();
    void Fill(const _ElementType& value);
};

template <typename _ElementType, int32_t Extent>
Span(_ElementType(&)[Extent]) -> Span<_ElementType, Extent>;

template <typename _ElementType, int32_t Extent>
Span(const _ElementType(&)[Extent]) -> Span<const _ElementType, Extent>;

template <typename _ElementType>
Span(_ElementType*, int32_t) -> Span<_ElementType>;

template <typename _ElementType>
Span(const _ElementType*, int32_t) -> Span<const _ElementType>;

//template <typename _ContainerType, int32_t Extent>
//Span(_ContainerType&) -> Span<typename _ContainerType::value_type, Extent>;
//
//template <typename _ContainerType, int32_t Extent>
//Span(const _ContainerType&)->Span<const typename _ContainerType::value_type, Extent>;

template <typename _ContainerType>
Span(_ContainerType&) -> Span<typename _ContainerType::value_type>;

template <typename _ContainerType>
Span(const _ContainerType&) -> Span<const typename _ContainerType::value_type>;

template <typename>
struct IsSpan : std::false_type {};

template <typename _ElementType, int32_t Extent>
struct IsSpan<Span<_ElementType, Extent>> : std::true_type {};

template <typename _ElementType, int32_t Extent>
constexpr bool IsSpanValue = IsSpan<_ElementType, Extent>::value;

template <typename _ElementType, int32_t Extent>
constexpr Span<_ElementType, Extent>::Span(PointerType ptr, int32_t count) noexcept :
    SpanStorageType(ptr, count)
{
}

template <typename _ElementType, int32_t Extent>
constexpr Span<_ElementType, Extent>::Span(_ElementType(&arr)[Extent]) noexcept :
    SpanStorageType(arr, Extent)
{
}

template <typename _ElementType, int32_t Extent>
constexpr typename Span<_ElementType, Extent>::ReferenceType Span<_ElementType, Extent>::operator[](int32_t index)
{
    TGON_EXPECT(index >= 0 && index < m_size);
    return m_data[index];
}

template <typename _ElementType, int32_t Extent>
constexpr typename Span<_ElementType, Extent>::ConstReferenceType Span<_ElementType, Extent>::operator[](int32_t index) const
{
    return const_cast<decltype(this)>->operator[](index);
}

template <typename _ElementType, int32_t Extent>
constexpr bool Span<_ElementType, Extent>::IsEmpty() const noexcept
{
    return m_size == 0;
}

template <typename _ElementType, int32_t Extent>
constexpr int32_t Span<_ElementType, Extent>::Length() const noexcept
{
    return m_size;
}

template<typename _ElementType, int32_t Extent>
constexpr Span<_ElementType> Span<_ElementType, Extent>::Slice(int32_t start) const
{
    TGON_EXPECT(start >= 0 && start <= m_size);
    return {m_data + start, m_size - start};
}

template<typename _ElementType, int32_t Extent>
constexpr Span<_ElementType> Span<_ElementType, Extent>::Slice(int32_t start, int32_t length) const
{
    TGON_EXPECT((start >= 0 && start <= length) && (length >= 0 && start + length <= m_size));
    return {m_data + start, length};
}

template <typename _ElementType, int32_t Extent>
template <int32_t Start, int32_t Length>
constexpr Span<_ElementType, Extent>::SubSpanType<Start, Length> Span<_ElementType, Extent>::Slice() const
{
    TGON_EXPECT((Start >= 0 && Start <= Length) && (Length != detail::DynamicExtent || Length <= Extent));
    return {m_data + Start, (Length != detail::DynamicExtent) ? Length : (Extent != detail::DynamicExtent) ? Extent - Start : detail::DynamicExtent};
}

template<typename _ElementType, int32_t Extent>
inline void Span<_ElementType, Extent>::Clear()
{
    for (int32_t i = 0; i < m_size; ++i)
    {
        m_data[i] = {};
    }
}

template <typename _ElementType, int32_t Extent>
inline void Span<_ElementType, Extent>::Fill(const _ElementType& value)
{
    for (int32_t i = 0; i < m_size; ++i)
    {
        m_data[i] = value;
    }
}

} /* namespace tgon */

#undef TGON_STRINGIFY
#undef TGON_EXPECT