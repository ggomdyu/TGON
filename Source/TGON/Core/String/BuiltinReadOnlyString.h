/**
 * @filename    BuiltinReadOnlyString.h
 * @author      ggomdyu
 * @date        08/06/2017
 */

#pragma once
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include "Core/String/StringTraits.h"

namespace tgon
{
namespace string
{

template <typename _CharType, std::size_t _CharArraySize>
class BuiltinReadOnlyString :
    private StringTraits<_CharType>
{
    static_assert(_CharArraySize > 0, "The array size of BuiltinReadOnlyString must be over than 0.");

/* @section Type definition */
public:
    using SizeType = decltype(_CharArraySize);

    using CharType = _CharType;
    using ReferenceType = CharType&;
    using ConstReferenceType = const CharType&;
    using IteratorType = CharType*;
    using ConstIteratorType = const CharType*;
    using PointerType = CharType*;
    using ConstPointerType = const CharType*;
    using ReverseIteratorType = std::reverse_iterator<IteratorType>;
    using ConstReverseIteratorType = std::reverse_iterator<ConstIteratorType>;

/* @section Ctor/Dtor */
public:
	constexpr BuiltinReadOnlyString(_CharType(&str)[_CharArraySize]) noexcept;

    template <std::size_t _CharArraySize2>
    bool operator==(const BuiltinReadOnlyString<_CharType, _CharArraySize2>& rhs) const;
    
    constexpr const _CharType operator[](std::size_t index) const;

/* @section Public method */
public:
    template <std::size_t _CharArraySize2>
    int32_t Compare(const BuiltinReadOnlyString<_CharType, _CharArraySize2>& rhs) const;
    template <std::size_t _CharArraySize2>
    std::size_t Find(const BuiltinReadOnlyString<_CharType, _CharArraySize2>& rhs) const;
    std::size_t Find(const BuiltinReadOnlyString& rhs) const;
    std::size_t Find(_CharType ch, std::size_t offset = 0) const;
    template <std::size_t _CharArraySize2>
    std::size_t Find(const _CharType(&str)[_CharArraySize2], std::size_t offset = 0) const;
    std::size_t Find(const _CharType* str, std::size_t offset, std::size_t strLen) const;
    constexpr const _CharType At(std::size_t index) const noexcept;
	constexpr const _CharType* CStr() const noexcept;
	constexpr std::size_t Length() const noexcept;

    constexpr ConstIteratorType begin() const noexcept;
    constexpr ConstIteratorType end() const noexcept;
    constexpr ConstIteratorType cbegin() const noexcept;
    constexpr ConstIteratorType cend() const noexcept;
    constexpr ConstReverseIteratorType rbegin() const noexcept;
    constexpr ConstReverseIteratorType rend() const noexcept;

/* @section Public variable */
public:
    using StringTraits<_CharType>::NPos;

/* @section Private variable */
private:
    const _CharType* m_str;
};

template<typename _CharType, std::size_t _CharArraySize>
constexpr BuiltinReadOnlyString<_CharType, _CharArraySize>::BuiltinReadOnlyString(_CharType(&str)[_CharArraySize]) noexcept :
	m_str(str)
{
}

template<typename _CharType, std::size_t _CharArraySize>
constexpr const _CharType BuiltinReadOnlyString<_CharType, _CharArraySize>::operator[](std::size_t index) const
{
    return m_str[index];
}

template <typename _CharType, std::size_t _CharArraySize>
constexpr const _CharType BuiltinReadOnlyString<_CharType, _CharArraySize>::At(std::size_t index) const noexcept
{
    return m_str[index];
}

template<typename _CharType, std::size_t _CharArraySize>
constexpr const _CharType* BuiltinReadOnlyString<_CharType, _CharArraySize>::CStr() const noexcept
{
    return m_str;
}

template<typename _CharType, std::size_t _CharArraySize>
constexpr std::size_t BuiltinReadOnlyString<_CharType, _CharArraySize>::Length() const noexcept
{
    return _CharArraySize - 1;
}

template <typename _CharType, std::size_t _CharArraySize>
constexpr BuiltinReadOnlyString<const typename std::decay<_CharType>::type, _CharArraySize> MakeBuiltinReadOnlyString(_CharType(&str)[_CharArraySize]) noexcept
{
    return {str};
}

template<typename _CharType, std::size_t _CharArraySize>
template<std::size_t _CharArraySize2>
inline bool BuiltinReadOnlyString<_CharType, _CharArraySize>::operator==(const BuiltinReadOnlyString<_CharType, _CharArraySize2>& rhs) const
{
    return StringTraits<_CharType>::Compare(m_str, _CharArraySize - 1, rhs.CStr(), _CharArraySize2 - 1) == 0;
}

template<typename _CharType, std::size_t _CharArraySize>
template<std::size_t _CharArraySize2>
inline int32_t BuiltinReadOnlyString<_CharType, _CharArraySize>::Compare(const BuiltinReadOnlyString<_CharType, _CharArraySize2>& rhs) const
{
    return StringTraits<_CharType>::Compare(m_str, _CharArraySize - 1, rhs.CStr(), _CharArraySize2 - 1);
}

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
inline std::size_t BuiltinReadOnlyString<_CharType, _CharArraySize>::Find(const BuiltinReadOnlyString<_CharType, _CharArraySize2>& rhs) const
{
    return StringTraits<_CharType>::Find(m_str, _CharArraySize - 1, rhs.CStr(), 0, _CharArraySize2 - 1);
}

template <typename _CharType, std::size_t _CharArraySize>
inline std::size_t BuiltinReadOnlyString<_CharType, _CharArraySize>::Find(const BuiltinReadOnlyString& rhs) const
{
    return StringTraits<_CharType>::Find(m_str, _CharArraySize - 1, rhs.CStr(), 0, _CharArraySize - 1);
}

template <typename _CharType, std::size_t _CharArraySize>
inline std::size_t BuiltinReadOnlyString<_CharType, _CharArraySize>::Find(_CharType ch, std::size_t offset) const
{
    return StringTraits<_CharType>::Find(m_str, _CharArraySize - 1, &ch, offset, 1);
}

template <typename _CharType, std::size_t _CharArraySize>
template <std::size_t _CharArraySize2>
inline std::size_t BuiltinReadOnlyString<_CharType, _CharArraySize>::Find(const _CharType(&str)[_CharArraySize2], std::size_t offset) const
{
    return StringTraits<_CharType>::Find(m_str, _CharArraySize - 1, str, offset, _CharArraySize2 - 1);
}

template <typename _CharType, std::size_t _CharArraySize>
inline std::size_t BuiltinReadOnlyString<_CharType, _CharArraySize>::Find(const _CharType* str, std::size_t offset, std::size_t count) const
{
    return StringTraits<_CharType>::Find(m_str, _CharArraySize - 1, str, offset, count);
}

template<typename _CharType, std::size_t _CharArraySize>
constexpr typename BuiltinReadOnlyString<_CharType, _CharArraySize>::ConstIteratorType BuiltinReadOnlyString<_CharType, _CharArraySize>::begin() const noexcept
{
    return this->cbegin();
}

template<typename _CharType, std::size_t _CharArraySize>
constexpr typename BuiltinReadOnlyString<_CharType, _CharArraySize>::ConstIteratorType BuiltinReadOnlyString<_CharType, _CharArraySize>::end() const noexcept
{
    return this->cend();
}

template <typename _CharType, std::size_t _CharArraySize>
constexpr typename BuiltinReadOnlyString<_CharType, _CharArraySize>::ConstIteratorType BuiltinReadOnlyString<_CharType, _CharArraySize>::cbegin() const noexcept
{
    return &m_str[0];
}

template <typename _CharType, std::size_t _CharArraySize>
constexpr typename BuiltinReadOnlyString<_CharType, _CharArraySize>::ConstIteratorType BuiltinReadOnlyString<_CharType, _CharArraySize>::cend() const noexcept
{
    return &m_str[_CharArraySize - 2];
}

template <typename _CharType, std::size_t _CharArraySize>
constexpr typename BuiltinReadOnlyString<_CharType, _CharArraySize>::ConstReverseIteratorType BuiltinReadOnlyString<_CharType, _CharArraySize>::rbegin() const noexcept
{
    return {this->end()};
}

template <typename _CharType, std::size_t _CharArraySize>
constexpr typename BuiltinReadOnlyString<_CharType, _CharArraySize>::ConstReverseIteratorType BuiltinReadOnlyString<_CharType, _CharArraySize>::rend() const noexcept
{
    return {this->begin()};
}

} /* namespace string */
} /* namespace tgon */