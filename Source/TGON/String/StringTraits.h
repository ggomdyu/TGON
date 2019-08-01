/**
 * @file    StringTraits.h
 * @author  ggomdyu
 * @date    08/06/2017
 */

#pragma once
#include <algorithm>
#include <cstdarg>
#include <cassert>
#include <cctype>
#include <string_view>
#include <memory>

namespace tgon
{

template <typename _CharType>
class BasicStringTraits
{
/**@section Type */
public:
    using ValueType = _CharType;
    using CharTraitsType = std::char_traits<_CharType>;

/**@section Constructor */
protected:
    constexpr BasicStringTraits() noexcept = default;

    /**
     * @brief   Assigns srcStr to destStr.
     * @param [in] srcStr               The string to copy.
     * @param [out] destStr             The destination of assign.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    BasicStringTraits(const std::basic_string_view<_CharType>& srcStr, _CharType* destStr, std::size_t destStrBufferLen);

    /**
     * @brief   Assigns srcStr to destStr.
     * @param [in] srcStr       The string to copy.
     * @param [out] destStr     The destination of assign.
     */
    template <std::size_t _DestStrBufferLen>
    BasicStringTraits(const std::basic_string_view<_CharType>& srcStr, _CharType(&destStr)[_DestStrBufferLen]);

    /**
     * @brief   Assigns the chCount copies of ch to destStr.
     * @param [out] destStr             The destination of assign.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     * @param [in] ch                   The character to assign to the string.
     * @param [in] chCount              The count of ch to assign to the string.
     */
    BasicStringTraits(_CharType* destStr, std::size_t destStrBufferLen, _CharType ch, std::size_t chCount = 1);

    /**
     * @brief   Assigns the chCount copies of ch to destStr.
     * @param [out] destStr     The destination of assign.
     * @param [in] ch           The character to assign to the string.
     * @param [in] chCount      The count of ch to assign to the string.
     */
    template <std::size_t _DestStrBufferLen>
    BasicStringTraits(_CharType(&destStr)[_DestStrBufferLen], _CharType ch, std::size_t chCount = 1) :
        BasicStringTraits(destStr, _DestStrBufferLen, ch, chCount)
    {
    }
    
/**@section Method */
public:
    /**
     * @brief   Assigns srcStr to destStr.
     * @param [in] srcStr               The string to copy.
     * @param [out] destStr             The destination of assign.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    static void Assign(const std::basic_string_view<_CharType>& srcStr, _CharType* destStr, std::size_t destStrBufferLen);

    /**
     * @brief   Assigns srcStr to destStr.
     * @param [in] srcStr       The string to copy.
     * @param [out] destStr     The destination of assign.
     */
    template <std::size_t _DestStrBufferLen>
    static void Assign(const std::basic_string_view<_CharType>& srcStr, _CharType* destStr)
    {
        Assign(srcStr, destStr, _DestStrBufferLen);
    }

    /**
     * @brief   Assigns the chCount copies of ch to destStr.
     * @param [out] destStr             The destination of assign.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     * @param [in] ch                   The character to assign to destStr.
     * @param [in] chCount              The count of ch to assign to destStr.
     */
    static void Assign(_CharType* destStr, std::size_t destStrBufferLen, _CharType ch, std::size_t chCount);
    
    /**
     * @brief   Assigns the chCount copies of ch to destStr.
     * @param [out] destStr     The destination of assign.
     * @param [in] ch           The character to assign to destStr.
     * @param [in] chCount      The count of ch to assign to destStr.
     */
    template <std::size_t _DestStrBufferLen>
    static void Assign(_CharType(&destStr)[_DestStrBufferLen], _CharType ch, std::size_t chCount)
    {
        Assign(destStr, _DestStrBufferLen, ch, chCount);
    }

    /**
     * @brief   Appends srcStr to destStr.
     * @param [in] srcStr               The string to append.
     * @param [out] destStr             The destination of append.
     * @param [in] destStrLen           The length of destStr.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    static void Append( const std::basic_string_view<_CharType>& srcStr, _CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferLen );

    /**
     * @brief   Appends srcStr to destStr.
     * @param [in] srcStr       The string to append.
     * @param [out] destStr     The destination of append.
     * @param [in] destStrLen   The length of destStr.
     */
    template <std::size_t _DestStrBufferLen>
    static void Append(const std::basic_string_view<_CharType>& srcStr, _CharType(&destStr)[_DestStrBufferLen], std::size_t destStrLen)
    {
        Append(srcStr, destStr, destStrLen, _DestStrBufferLen);
    }

    /**
     * @brief   Appends the chCount copies of ch to destStr.
     * @param [out] destStr             The destination of append.
     * @param [in] destStrLen           The length of destStr.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     * @param [in] ch                   The character to append to destStr.
     * @param [in] chCount              The count of ch to append to destStr.
     */
    static void Append(_CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferLen, _CharType ch, std::size_t chCount = 1);

    /**
     * @brief   Appends the chCount copies of ch to destStr.
     * @param [out] destStr     The destination of append.
     * @param [in] destStrLen   The length of destStr.
     * @param [in] ch           The character to append to destStr.
     * @param [in] chCount      The count of ch to append to destStr.
     */
    template <std::size_t _DestStrBufferLen>
    static void Append(_CharType(&destStr)[_DestStrBufferLen], std::size_t destStrLen, _CharType ch, std::size_t chCount = 1)
    {
        Append(destStr, destStrLen, _DestStrBufferLen, ch, chCount);
    }

    /**
     * @brief   Searches a matching substring.
     * @param [in] srcStr           The string to find.
     * @param [in] srcStrOffset     The point of srcStr which start to search.
     * @param [in] srcSubStr        The substring to find.
     * @param [in] srcSubStrLen     The length of srcSubStr.
     */
    static std::size_t Find(const std::basic_string_view<_CharType>& srcStr, std::size_t srcStrOffset, const _CharType* srcSubStr, std::size_t srcSubStrLen);

    /**
     * @brief   Searches a last matching substring.
     * @param [in] srcStr           The string to find.
     * @param [in] srcStrOffset     The point of srcStr which start to search.
     * @param [in] srcSubStr        The substring to find.
     */
    static std::size_t RFind(const std::basic_string_view<_CharType>& srcStr, std::size_t srcStrOffset, const std::basic_string_view<_CharType>& srcSubStr);

    static int32_t Compare(const std::basic_string_view<_CharType>& srcLhsStr, const std::basic_string_view<_CharType>& srcRhsStr);

    /**
     * @brief   Returns a reference to the character specified by index.
     * @return                  The reference to the character.
     * @param [in] srcStr       The source or string to index.
     * @param [in] index        The index which indicates position of character within string.
     */
    static _CharType& At(_CharType* srcStr, std::size_t index);
    
    /**
     * @brief   Returns a reference to the character specified by index.
     * @return                  The reference to the character.
     * @param [in] srcStr       The source or string to index.
     * @param [in] index        The index which indicates position of character within string.
     */
    static const _CharType& At(const _CharType* srcStr, std::size_t index);

    /**
     * @brief   Returns the length of srcStr.
     * @return              The length of srcStr.
     * @param [in] srcStr   The source of string.
     */
    static std::size_t Length(const _CharType* srcStr);

    /**
     * @brief   Swaps the contents of strings.
     * @param [in] srcStr              The string to be swapped with destStr.
     * @param [in] srcStrLen           The length of srcStr.
     * @param [in] srcStrBufferLen     The buffer length of srcStr.
     * @param [in] destStr             The string to be swapped with srcStr.
     * @param [in] destStrLen          The length of destStr.
     * @param [in] destStrBufferLen    The buffer length of destStr.
     */
    static void Swap(_CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrBufferLen, _CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferLen);

    /**
     * @brief   Converts the content of string to lowercase.
     * @param [in] srcStr               The source or string to convert.
     * @param [in] destStr              The destination of convert.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    static void ToLower(const std::basic_string_view<_CharType>& srcStr, _CharType* destStr, std::size_t destStrBufferLen);

    /**
     * @brief   Converts the content of string to lowercase.
     * @param [in] srcStr               The source or string to convert.
     * @param [in] destStr              The destination of convert.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    static std::size_t ToLower(const _CharType* srcStr, _CharType* destStr, std::size_t destStrBufferLen);

    /**
     * @brief   Converts the content of string to uppercase.
     * @param [in] srcStr               The source or string to convert.
     * @param [in] destStr              The destination of convert.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    static void ToUpper(const std::basic_string_view<_CharType>& srcStr, _CharType* destStr, std::size_t destStrBufferLen);

    /**
     * @brief   Converts the content of string to uppercase.
     * @param [in] srcStr               The source or string to convert.
     * @param [in] destStr              The destination of convert.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    static std::size_t ToUpper(const _CharType* srcStr, _CharType* destStr, std::size_t destStrBufferLen);

    /**
     * @brief   Checks the string is null or empty.
     * @return  True if the string is null or empty, false otherwise.
     */
    static bool IsNullOrEmpty(const _CharType* srcStr) noexcept;
    
    /**
     * @brief   Replaces each format item in formatStr to text.
     * @param [in] formatStr    The format string.
     * @return  Returns a pair, which its first member is replaced string. The second member is length of format string if succeed, -1 otherwise.
     */
    static std::basic_string_view<_CharType> Format(const _CharType* formatStr, ...);
    
    /**
     * @brief   Replaces each format item in formatStr to text.
     * @param [in] formatStr    The format string.
     * @return  Returns a pair, which its first member is replaced string. The second member is length of format string if succeed, -1 otherwise.
     */
    static std::basic_string_view<_CharType> Format(const _CharType* formatStr, std::va_list vaList);

/**@section Variable */
public:
    /**
     * @brief   This is a special magic number which means string does not exist.
     *          The series of find function will return this variable when substring search fails.
     */
    static constexpr const std::size_t NPos = static_cast<std::size_t>(-1);
};

using StringTraits = BasicStringTraits<char>;
using WStringTraits = BasicStringTraits<wchar_t>;

template <typename _CharType>
inline BasicStringTraits<_CharType>::BasicStringTraits(const std::basic_string_view<_CharType>& srcStr, _CharType* destStr, std::size_t destStrBufferLen)
{
    BasicStringTraits::Assign(srcStr, destStr, destStrBufferLen);
}

template <typename _CharType>
template <std::size_t _DestStrBufferLen>
inline BasicStringTraits<_CharType>::BasicStringTraits(const std::basic_string_view<_CharType>& srcStr, _CharType(&destStr)[_DestStrBufferLen]) :
    BasicStringTraits(srcStr, destStr, _DestStrBufferLen)
{
}
    
template <typename _CharType>
inline BasicStringTraits<_CharType>::BasicStringTraits(_CharType* destStr, std::size_t destStrBufferLen, _CharType ch, std::size_t chCount)
{
    BasicStringTraits::Assign(destStr, destStrBufferLen, ch, chCount);
}

template <typename _CharType>
inline void BasicStringTraits<_CharType>::Assign(const std::basic_string_view<_CharType>& srcStr, _CharType* destStr, std::size_t destStrBufferLen)
{
    assert(destStrBufferLen > srcStr.length() && "String buffer overflowed!");

    memcpy(destStr, srcStr.data(), sizeof(_CharType) * (srcStr.length() + 1));

    destStr[srcStr.length()] = _CharType();
}

template <typename _CharType>
inline void BasicStringTraits<_CharType>::Assign(_CharType* destStr, std::size_t destStrBufferLen, _CharType ch, std::size_t chCount)
{
    assert(destStrBufferLen > chCount && "String buffer overflowed!");

    std::size_t i = 0;
    while (i < chCount)
    {
        destStr[i++] = ch;
    }

    destStr[i] = _CharType();
}

template<typename _CharType>
inline void BasicStringTraits<_CharType>::Append(const std::basic_string_view<_CharType>& srcStr, _CharType * destStr, std::size_t destStrLen, std::size_t destStrBufferLen)
{
    assert(destStrBufferLen > srcStr.length() + destStrLen && "String buffer overflowed!");

    memcpy(&destStr[destStrLen], srcStr.data(), sizeof(_CharType) * (srcStr.length() + 1));
}

template <typename _CharType>
inline void BasicStringTraits<_CharType>::Append(_CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferLen, _CharType ch, std::size_t chCount)
{
    assert(destStrBufferLen > chCount + destStrLen && "String buffer overflowed!");

    chCount += destStrLen;
    while (destStrLen < chCount)
    {
        destStr[destStrLen++] = ch;
    }

    destStr[destStrLen] = _CharType();
}

template <typename _CharType>
inline std::size_t BasicStringTraits<_CharType>::Find(const std::basic_string_view<_CharType>& srcStr, std::size_t srcStrOffset, const _CharType* srcSubStr, std::size_t srcSubStrLen)
{
    const _CharType* foundStr = std::search(srcStr + srcStrOffset, srcStr + srcStr.length(), srcSubStr, srcSubStr + srcSubStrLen);
    if (foundStr != srcStr + srcStr.length())
    {
        return static_cast<std::size_t>(foundStr - srcStr);
    }

    return NPos;
}

template <typename _CharType>
inline std::size_t BasicStringTraits<_CharType>::RFind(const std::basic_string_view<_CharType>& srcStr, std::size_t srcStrOffset, const std::basic_string_view<_CharType>& srcSubStr)
{
    const _CharType* foundStr = std::find_end(srcStr + srcStrOffset, srcStr + srcStr.length(), srcSubStr, srcSubStr + srcSubStr.length());
    if (foundStr != srcStr + srcStr.length())
    {
        return static_cast<std::size_t>(foundStr - srcStr);
    }

    return NPos;
}

template <typename _CharType>
inline int32_t BasicStringTraits<_CharType>::Compare(const std::basic_string_view<_CharType>& srcLhsStr, const std::basic_string_view<_CharType>& srcRhsStr)
{
    auto ans = CharTraitsType::compare(srcLhsStr.data(), srcRhsStr.data(), std::min(srcLhsStr.length(), srcRhsStr.length()));
    if (ans != 0)
    {
        return ans;
    }

    if (srcLhsStr.length() < srcRhsStr.length())
    {
        return -1;
    }
    if (srcLhsStr.length() > srcRhsStr.length())
    {
        return 1;
    }
    
    return 0;
}

template <typename _CharType>
inline _CharType& BasicStringTraits<_CharType>::At(_CharType* srcStr, std::size_t index)
{
    return srcStr[index];
}

template <typename _CharType>
inline const _CharType& BasicStringTraits<_CharType>::At(const _CharType* srcStr, std::size_t index)
{
    return srcStr[index];
}
    
template <typename _CharType>
inline std::size_t BasicStringTraits<_CharType>::Length(const _CharType* srcStr)
{
    return CharTraitsType::length(srcStr);
}

template <typename _CharType>
inline void BasicStringTraits<_CharType>::Swap(_CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrBufferLen, _CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferLen)
{
    std::swap_ranges(srcStr, srcStr + srcStrLen, destStr);
}

template <typename _CharType>
inline void BasicStringTraits<_CharType>::ToLower(const std::basic_string_view<_CharType>& srcStr, _CharType* destStr, std::size_t destStrBufferLen)
{
    assert(destStrBufferLen > srcStr.length() && "String buffer overflowed!");

    std::transform(srcStr.data(), srcStr.data() + srcStr.length() + 1, destStr, ::tolower);
}

template <typename _CharType>
inline std::size_t BasicStringTraits<_CharType>::ToLower(const _CharType* srcStr, _CharType* destStr, std::size_t destStrBufferLen)
{
    std::size_t srcStrLen = std::strlen(srcStr);
    ToLower({srcStr, srcStrLen}, destStr, destStrBufferLen);
    
    return srcStrLen;
}

template <typename _CharType>
inline void BasicStringTraits<_CharType>::ToUpper(const std::basic_string_view<_CharType>& srcStr, _CharType* destStr, std::size_t destStrBufferLen)
{
    assert(destStrBufferLen > srcStr.length() && "String buffer overflowed!");

    std::transform(srcStr.data(), srcStr.data() + srcStr.length() + 1, destStr, ::toupper);
}

template <typename _CharType>
inline std::size_t BasicStringTraits<_CharType>::ToUpper(const _CharType* srcStr, _CharType* destStr, std::size_t destStrBufferLen)
{
    std::size_t srcStrLen = std::strlen(srcStr);
    ToUpper({srcStr, srcStrLen}, destStr, destStrBufferLen);
    
    return srcStrLen;
}

template <typename _CharType>
inline bool BasicStringTraits<_CharType>::IsNullOrEmpty(const _CharType* srcStr) noexcept
{   
    if (srcStr == nullptr || srcStr[0] == _CharType(0))
    {
        return true;
    }

    return false;
}
    
template <typename _CharType>
inline std::basic_string_view<_CharType> BasicStringTraits<_CharType>::Format(const _CharType* formatStr, ...)
{
    std::va_list vaList;
    va_start(vaList, formatStr);

    return Format(formatStr, vaList);
}

template <>
inline std::string_view BasicStringTraits<char>::Format(const char* formatStr, std::va_list vaList)
{
    constexpr std::size_t strBufferSize = 1024 * 8;
    thread_local static std::unique_ptr<char[]> strBuffer(new char[strBufferSize] {});

#ifdef _MSC_VER
    int strLen = vsprintf_s(strBuffer.get(), strBufferSize, formatStr, vaList);
#else
    int strLen = vsprintf(strBuffer.get(), formatStr, vaList);
#endif
    return std::string_view(strBuffer.get(), strLen);
}
    
template <>
inline std::wstring_view BasicStringTraits<wchar_t>::Format(const wchar_t* formatStr, std::va_list vaList)
{
    constexpr std::size_t strBufferSize = 1024 * 8;
    thread_local static std::unique_ptr<wchar_t[]> strBuffer(new wchar_t[strBufferSize] {});
    
#ifdef _MSC_VER
    int strLen = vswprintf_s(strBuffer.get(), strBufferSize, formatStr, vaList);
#else
    int strLen = vswprintf(strBuffer.get(), strBufferSize, formatStr, vaList);
#endif
    return std::wstring_view(strBuffer.get(), strLen);
}

} /* namespace tgon */
