/**
 * @filename    StringTraits.h
 * @author      ggomdyu
 * @date        08/06/2017
 */

#pragma once
#include <algorithm>
#include <cassert>

namespace tgon
{

template <typename _CharType>
class StringTraits
{
/* @section Public type */
public:
    using CharTraitsType = std::char_traits<_CharType>;

/* @section Protected constructor */
protected:
    constexpr StringTraits() noexcept = default;

    /**
     * @brief                           Assigns srcStr to destStr.
     * @param [in] srcStr               The string to copy.
     * @param [in] srcStrLen            The length of srcStr.
     * @param [out] destStr             The destination of assign.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    StringTraits(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrBufferLen);

    /**
     * @brief                           Assigns srcStr to destStr.
     * @param [in] srcStr               The string to copy.
     * @param [in] srcStrLen            The length of srcStr.
     * @param [out] destStr             The destination of assign.
     */
    template <std::size_t _DestStrBufferLen>
    StringTraits(const _CharType* srcStr, std::size_t srcStrLen, _CharType(&destStr)[_DestStrBufferLen]) :
        StringTraits(srcStr, srcStrLen, destStr, _DestStrBufferLen)
    {
    }

    /**
     * @brief                           Assigns the chCount copies of ch to destStr.
     * @param [out] destStr             The destination of assign.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     * @param [in] ch                   The character to assign to the string.
     * @param [in] chCount              The count of ch to assign to the string.
     */
    StringTraits(_CharType* destStr, std::size_t destStrBufferLen, _CharType ch, std::size_t chCount = 1);

    /**
     * @brief                           Assigns the chCount copies of ch to destStr.
     * @param [out] destStr             The destination of assign.
     * @param [in] ch                   The character to assign to the string.
     * @param [in] chCount              The count of ch to assign to the string.
     */
    template <std::size_t _DestStrBufferLen>
    StringTraits(_CharType(&destStr)[_DestStrBufferLen], _CharType ch, std::size_t chCount = 1) :
        StringTraits(destStr, _DestStrBufferLen, ch, chCount)
    {
    }
    
/* @section Public method */
public:
    /**
     * @brief                           Assigns srcStr to destStr.
     * @param [in] srcStr               The string to copy.
     * @param [in] srcStrLen            The length of srcStr.
     * @param [out] destStr             The destination of assign.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    static void Assign(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrBufferLen);

    /**
     * @brief                           Assigns srcStr to destStr.
     * @param [in] srcStr               The string to copy.
     * @param [in] srcStrLen            The length of srcStr.
     * @param [out] destStr             The destination of assign.
     */
    template <std::size_t _DestStrBufferLen>
    static void Assign(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr)
    {
        Assign(srcStr, srcStrLen, destStr, _DestStrBufferLen);
    }

    /**
     * @brief                           Assigns the chCount copies of ch to destStr.
     * @param [out] destStr             The destination of assign.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     * @param [in] ch                   The character to assign to destStr.
     * @param [in] chCount              The count of ch to assign to destStr.
     */
    static void Assign(_CharType* destStr, std::size_t destStrBufferLen, _CharType ch, std::size_t chCount);
    
    /**
     * @brief                           Assigns the chCount copies of ch to destStr.
     * @param [out] destStr             The destination of assign.
     * @param [in] ch                   The character to assign to destStr.
     * @param [in] chCount              The count of ch to assign to destStr.
     */
    template <std::size_t _DestStrBufferLen>
    static void Assign(_CharType(&destStr)[_DestStrBufferLen], _CharType ch, std::size_t chCount)
    {
        Assign(destStr, _DestStrBufferLen, ch, chCount);
    }

    /**
     * @brief                           Appends srcStr to destStr.
     * @param [in] srcStr               The string to append.
     * @param [in] srcStrLen            The length of srcStr.
     * @param [out] destStr             The destination of append.
     * @param [in] destStrLen           The length of destStr.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    static void Append(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferLen);

    /**
     * @brief                           Appends srcStr to destStr.
     * @param [in] srcStr               The string to append.
     * @param [in] srcStrLen            The length of srcStr.
     * @param [out] destStr             The destination of append.
     * @param [in] destStrLen           The length of destStr.
     */
    template <std::size_t _DestStrBufferLen>
    static void Append(const _CharType* srcStr, std::size_t srcStrLen, _CharType(&destStr)[_DestStrBufferLen], std::size_t destStrLen)
    {
        Append(srcStr, srcStrLen, destStr, destStrLen, _DestStrBufferLen);
    }

    /**
     * @brief                           Appends the chCount copies of ch to destStr.
     * @param [out] destStr             The destination of append.
     * @param [in] destStrLen           The length of destStr.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     * @param [in] ch                   The character to append to destStr.
     * @param [in] chCount              The count of ch to append to destStr.
     */
    static void Append(_CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferLen, _CharType ch, std::size_t chCount = 1);

    /**
     * @brief                           Appends the chCount copies of ch to destStr.
     * @param [out] destStr             The destination of append.
     * @param [in] destStrLen           The length of destStr.
     * @param [in] ch                   The character to append to destStr.
     * @param [in] chCount              The count of ch to append to destStr.
     */
    template <std::size_t _DestStrBufferLen>
    static void Append(_CharType(&destStr)[_DestStrBufferLen], std::size_t destStrLen, _CharType ch, std::size_t chCount = 1)
    {
        Append(destStr, destStrLen, _DestStrBufferLen, ch, chCount);
    }

    /**
     * @brief                           Searches a matching substring.
     * @param [in] srcStr               The string to find.
     * @param [in] srcStrLen            The length of srcStr.
     * @param [in] srcStrOffset         The point of srcStr which start to search.
     * @param [in] srcSubStr            The substring to find.
     * @param [in] srcSubStrLen         The length of srcSubStr.
     */
    static std::size_t Find(const _CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrOffset, const _CharType* srcSubStr, std::size_t srcSubStrLen);

    /**
     * @brief                           Searches a last matching substring.
     * @param [in] srcStr               The string to find.
     * @param [in] srcStrLen            The length of srcStr.
     * @param [in] srcStrOffset         The point of srcStr which start to search.
     * @param [in] srcSubStr            The substring to find.
     * @param [in] srcSubStrLen         The length of srcSubStr.
     */
    static std::size_t RFind(const _CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrOffset, const _CharType* srcSubStr, std::size_t srcSubStrLen);

    static int32_t Compare(const _CharType* srcLhsStr, std::size_t srcLhsStrLen, const _CharType* srcRhsStr, std::size_t srcRhsStrLen);

    /**
     * @brief                           Returns a reference to the character specified by index.
     * @return                          The reference to the character.
     * @param [in] srcStr               The source or string to index.
     * @param [in] srcStrLen            The length of srcStr.
     * @param [in] index                The index which indicates position of character within string.
     */
    static _CharType& At(_CharType* srcStr, std::size_t srcStrLen, std::size_t index);
    
    /**
     * @brief                           Returns a reference to the character specified by index.
     * @return                          The reference to the character.
     * @param [in] srcStr               The source or string to index.
     * @param [in] srcStrLen            The length of srcStr.
     * @param [in] index                The index which indicates position of character within string.
     */
    static const _CharType& At(const _CharType* srcStr, std::size_t srcStrLen, std::size_t index);

    /**
     * @brief                           Returns the length of srcStr.
     * @return                          The length of srcStr.
     * @param [in] srcStr               The source of string.
     */
    static std::size_t Length(const _CharType* srcStr);

    /**
     * @brief                           Swaps the contents of strings.
     * @param [in] srcStr               The string to be swapped with destStr.
     * @param [in] srcStrLen            The length of srcStr.
     * @param [in] srcStrBufferSize     The buffer length of srcStr.
     * @param [in] destStr              The string to be swapped with srcStr.
     * @param [in] destStrLen           The length of destStr.
     * @param [in] destStrBufferSize    The buffer length of destStr.
     */
    static void Swap(_CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrBufferSize, _CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferLen);

    /**
     * @brief                           Converts the content of string to lowercase.
     * @param [in] srcStr               The source or string to convert.
     * @param [in] srcStrLen            The length of srcStr
     * @param [in] destStr              The destination of convert.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    static void ToLower(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrBufferLen);

    /**
     * @brief                           Converts the content of string to lowercase.
     * @param [in] srcStr               The source or string to convert.
     * @param [in] destStr              The destination of convert.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    static void ToLower(const _CharType* srcStr, _CharType* destStr, std::size_t destStrBufferLen);

    /**
     * @brief                           Converts the content of string to uppercase.
     * @param [in] srcStr               The source or string to convert.
     * @param [in] srcStrLen            The length of srcStr
     * @param [in] destStr              The destination of convert.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    static void ToUpper(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrBufferLen);

    /**
     * @brief                           Converts the content of string to uppercase.
     * @param [in] srcStr               The source or string to convert.
     * @param [in] destStr              The destination of convert.
     * @param [in] destStrBufferLen     The buffer length of destStr.
     */
    static void ToUpper(const _CharType* srcStr, _CharType* destStr, std::size_t destStrBufferLen);

    /**
     * @brief                           Checks the string is null or empty.
     * @return                          True if the string is null or empty, false otherwise.
     */
    static bool IsNullOrEmpty(const _CharType* srcStr) noexcept;

/* @section Public variable */
public:
    /**
     * @brief   This is a special magic number which means string does not exist.
     *          The series of find function will return this variable when substring searching fails.
     */
    static constexpr const std::size_t NPos = static_cast<std::size_t>(-1);
};

template <typename _CharType>
inline StringTraits<_CharType>::StringTraits(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrBufferLen)
{
    StringTraits::Assign(srcStr, srcStrLen, destStr, destStrBufferLen);
}

template <typename _CharType>
inline StringTraits<_CharType>::StringTraits(_CharType* destStr, std::size_t destStrBufferLen, _CharType ch, std::size_t chCount)
{
    StringTraits::Assign(destStr, destStrBufferLen, ch, chCount);
}

template <typename _CharType>
inline void StringTraits<_CharType>::Assign(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrBufferLen)
{
    assert(destStrBufferLen > srcStrLen && "String buffer overflowed!");

    memcpy(destStr, srcStr, sizeof(_CharType) * (srcStrLen + 1));

    destStr[srcStrLen] = _CharType();
}

template <typename _CharType>
inline void StringTraits<_CharType>::Assign(_CharType* destStr, std::size_t destStrBufferLen, _CharType ch, std::size_t chCount)
{
    assert(destStrBufferLen > chCount && "String buffer overflowed!");

    std::size_t i = 0;
    while (i < chCount)
    {
        destStr[i++] = ch;
    }

    destStr[i] = _CharType();
}

template <typename _CharType>
inline void StringTraits<_CharType>::Append(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferLen)
{
    assert(destStrBufferLen > srcStrLen + destStrLen && "String buffer overflowed!");

    memcpy(&destStr[destStrLen], srcStr, sizeof(_CharType) * (srcStrLen + 1));
}

template <typename _CharType>
inline void StringTraits<_CharType>::Append(_CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferLen, _CharType ch, std::size_t chCount)
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
inline std::size_t StringTraits<_CharType>::Find(const _CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrOffset, const _CharType* srcSubStr, std::size_t srcSubStrLen)
{
    const _CharType* foundStr = std::search(srcStr + srcStrOffset, srcStr + srcStrLen, srcSubStr, srcSubStr + srcSubStrLen);
    if (foundStr != srcStr + srcStrLen)
    {
        return static_cast<std::size_t>(foundStr - srcStr);
    }

    return NPos;
}

template <typename _CharType>
inline std::size_t StringTraits<_CharType>::RFind(const _CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrOffset, const _CharType* srcSubStr, std::size_t srcSubStrLen)
{
    const _CharType* foundStr = std::find_end(srcStr + srcStrOffset, srcStr + srcStrLen, srcSubStr, srcSubStr + srcSubStrLen);
    if (foundStr != srcStr + srcStrLen)
    {
        return static_cast<std::size_t>(foundStr - srcStr);
    }

    return NPos;
}

template <typename _CharType>
inline int32_t StringTraits<_CharType>::Compare(const _CharType* srcLhsStr, std::size_t srcLhsStrLen, const _CharType* srcRhsStr, std::size_t srcRhsStrLen)
{
    auto ans = CharTraitsType::compare(srcLhsStr, srcRhsStr, std::min(srcLhsStrLen, srcRhsStrLen));
    if (ans != 0)
    {
        return ans;
    }

    if (srcLhsStrLen < srcRhsStrLen)
    {
        return -1;
    }
    if (srcLhsStrLen > srcRhsStrLen)
    {
        return 1;
    }
    
    return 0;
}

template <typename _CharType>
inline _CharType& StringTraits<_CharType>::At(_CharType* srcStr, std::size_t srcStrLen, std::size_t index)
{
    assert(index <= srcStrLen && "String index out of range!");

    return srcStr[index];
}

template <typename _CharType>
inline const _CharType& StringTraits<_CharType>::At(const _CharType* srcStr, std::size_t srcStrLen, std::size_t index)
{
    assert(index <= srcStrLen && "String index out of range!");

    return srcStr[index];
}
    
template <typename _CharType>
inline std::size_t StringTraits<_CharType>::Length(const _CharType* srcStr)
{
    return CharTraitsType::length(srcStr);
}

template <typename _CharType>
inline void StringTraits<_CharType>::Swap(_CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrBufferSize, _CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferLen)
{
    std::swap_ranges(srcStr, srcStr + srcStrLen, destStr);
}

template <typename _CharType>
inline void StringTraits<_CharType>::ToLower(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrBufferLen)
{
    assert(destStrBufferLen > srcStrLen && "String buffer overflowed!");

    std::transform(srcStr, srcStr + srcStrLen + 1, destStr, ::tolower);
}

template <typename _CharType>
inline void StringTraits<_CharType>::ToLower(const _CharType* srcStr, _CharType* destStr, std::size_t destStrBufferLen)
{
    ToLower(srcStr, std::strlen(srcStr), destStr, destStrBufferLen);
}

template <typename _CharType>
inline void StringTraits<_CharType>::ToUpper(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrBufferLen)
{
    assert(destStrBufferLen > srcStrLen && "String buffer overflowed!");

    std::transform(srcStr, srcStr + srcStrLen + 1, destStr, ::tolower);
}

template <typename _CharType>
inline void StringTraits<_CharType>::ToUpper(const _CharType* srcStr, _CharType* destStr, std::size_t destStrBufferLen)
{
    ToUpper(srcStr, std::strlen(srcStr), destStr, destStrBufferLen);
}

template <typename _CharType>
inline bool StringTraits<_CharType>::IsNullOrEmpty(const _CharType* srcStr) noexcept
{   
    if (srcStr == nullptr)
    {
        return true;
    }

    if (srcStr[0] == 0)
    {
        return true;
    }

    return false;
}

} /* namespace tgon */