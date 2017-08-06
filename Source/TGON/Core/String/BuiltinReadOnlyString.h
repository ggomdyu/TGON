/**
 * @filename    FixedString.h
 * @author      ggomdyu
 * @date        08/06/2017
 */

template <typename _CharType, std::size_t _CharArraySize>
class BuiltinReadOnlyString
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
    constexpr BuiltinReadOnlyString(_CharType(&str)[_CharArraySize]) noexcept :
    m_str(str)
    {
    }

    template <std::size_t _CharArraySize2>
    constexpr bool operator==(const BuiltinReadOnlyString<_CharType, _CharArraySize2>& rhs) const;

    constexpr const _CharType operator[](std::size_t index) const
    {
        return m_str[index];
    }

    /* @section Public method */
public:
    template <std::size_t _CharArraySize2>
    int32_t Compare(const BuiltinReadOnlyString<_CharType, _CharArraySize2>& rhs) const;

    template <std::size_t _CharArraySize2>
    std::size_t Find(const BuiltinReadOnlyString<_CharType, _CharArraySize2>& rhs) const;
    std::size_t Find(const BuiltinReadOnlyString& rhs) const;
    std::size_t Find(_CharType ch, std::size_t offset = 0) const;
    template <std::size_t _BufferSize>
    std::size_t Find(const _CharType(&str)[_BufferSize], std::size_t offset = 0) const;
    std::size_t Find(const _CharType* str, std::size_t offset, std::size_t strLen) const;

    //    template <std::size_t _CharArraySize2>
    //    std::size_t Rfind(const BasicFixedString<_CharType, _CharArraySize2>& rhs) const;
    //    std::size_t Rfind(const BasicFixedString& rhs) const;
    //    std::size_t Rfind(_CharType ch, std::size_t offset = 0) const;
    //    template <std::size_t _BufferSize>
    //    std::size_t Rfind(const _CharType(&str)[_BufferSize], std::size_t offset = 0) const;
    //    std::size_t Rfind(const _CharType* str, std::size_t offset, std::size_t count) const;

    _CharType& At(std::size_t index);
    const _CharType At(std::size_t index) const;

    const _CharType* CStr() const noexcept;

    std::size_t Length() const noexcept;

    IteratorType begin() noexcept;
    IteratorType end();
    ConstIteratorType cbegin() const noexcept;
    ConstIteratorType cend() const;
    ReverseIteratorType rbegin();
    ReverseIteratorType rend() noexcept;
    ConstReverseIteratorType rbegin() const;
    ConstReverseIteratorType rend() const noexcept;

    /* @section Public variable */
public:
    //using StringTraits<_CharType>::NPos;

    /* @section Private variable */

private:
    _CharType* m_str;
};

template <typename _CharType, std::size_t _CharArraySize>
inline typename tgon::string::BasicFixedString<_CharType, _CharArraySize>::IteratorType tgon::string::BasicFixedString<_CharType, _CharArraySize>::begin() noexcept
{
    return &m_str[0];
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename tgon::string::BasicFixedString<_CharType, _CharArraySize>::IteratorType tgon::string::BasicFixedString<_CharType, _CharArraySize>::end()
{
    return &m_str[m_length];
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename tgon::string::BasicFixedString<_CharType, _CharArraySize>::ConstIteratorType tgon::string::BasicFixedString<_CharType, _CharArraySize>::cbegin() const noexcept
{
    return &m_str[0];
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename tgon::string::BasicFixedString<_CharType, _CharArraySize>::ConstIteratorType tgon::string::BasicFixedString<_CharType, _CharArraySize>::cend() const
{
    return &m_str[m_length];
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename tgon::string::BasicFixedString<_CharType, _CharArraySize>::ReverseIteratorType tgon::string::BasicFixedString<_CharType, _CharArraySize>::rbegin()
{
    return {this->end()};
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename tgon::string::BasicFixedString<_CharType, _CharArraySize>::ReverseIteratorType tgon::string::BasicFixedString<_CharType, _CharArraySize>::rend() noexcept
{
    return {this->begin()};
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename tgon::string::BasicFixedString<_CharType, _CharArraySize>::ConstReverseIteratorType tgon::string::BasicFixedString<_CharType, _CharArraySize>::rbegin() const
{
    return {this->end()};
}

template <typename _CharType, std::size_t _CharArraySize>
inline typename tgon::string::BasicFixedString<_CharType, _CharArraySize>::ConstReverseIteratorType tgon::string::BasicFixedString<_CharType, _CharArraySize>::rend() const noexcept
{
    return {this->begin()};
}

template <typename _CharType, std::size_t _CharArraySize>
inline _CharType& tgon::string::BasicFixedString<_CharType, _CharArraySize>::At(std::size_t index)
{
    assert(index <= m_length && "BasicFixedString index out of range");

    return m_str[index];
}

template <typename _CharType, std::size_t _CharArraySize>
inline const _CharType BasicFixedString<_CharType, _CharArraySize>::At(std::size_t index) const
{
    assert(index <= m_length && "BasicFixedString index out of range");

    return m_str[index];
}


template <typename _CharType, std::size_t _CharArraySize>
constexpr BuiltinReadOnlyString<const typename std::decay<_CharType>::type, _CharArraySize> MakeBuiltinReadOnlyString(_CharType(&str)[_CharArraySize]) noexcept
{
    return {str};
}

