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
namespace string
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
     * @brief                   Copy string from source to destination.
     * @param [in] srcStr       The string to copy.
     * @param [in] srcStrLen    The length of string to copy.
     * @param [in] destStr      The destination of string to copy.
     */
    StringTraits(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrBufferSize);

    /**
     * @brief                   Assigns a number of character to string.
     * @param [out] destStr     The destination of assign
     * @param [in] ch           The character to assign to the string
     * @param [in] chCount      The character count to assign to the string
     */
    StringTraits(_CharType* destStr, std::size_t destStrBufferSize, _CharType ch, std::size_t chCount);

/* @section Public variable */
public:
    /**
     * @brief   This is the special magic number which means string not exists.
     *          The function series of Find will return this variable when searching sub-string failed.
     */
    static constexpr std::size_t NPos = static_cast<std::size_t>(-1);

/* @section Protected method */
protected:
    /**
     * @brief                   Copy string from source to destination.
     * @param [in] srcStr       The string to copy.
     * @param [in] srcStrLen    The length of string to copy.
     * @param [in] destStr      The destination of string to copy.
     */
    static void Assign(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrBufferSize);

    /**
     * @brief                   Assigns a number of character to string.
     * @param [out] destStr     The destination of assign
     * @param [in] ch           The character to assign to the string
     * @param [in] chCount      The character count to assign to the string
     */
    static void Assign(_CharType* destStr, std::size_t destStrBufferSize, _CharType ch, std::size_t chCount);
    
    static void Append(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferSize);

    /**
     * @brief                   Appends a number of character to string.
     * @param [out] destStr     The destination of assign
     * @param [in] ch           The character to assign to the string
     * @param [in] chCount      The character count to assign to the string
     */
    static void Append(_CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferSize, _CharType ch, std::size_t chCount = 1);

    static std::size_t Find(const _CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrOffset, const _CharType* srcFindSubStr, std::size_t srcFindSubStrLen);

    static std::size_t RFind(const _CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrOffset, const _CharType* srcFindSubStr, std::size_t srcFindSubStrLen);

    static int32_t Compare(const _CharType* lhsStr, std::size_t lhsStrLen, const _CharType* rhsStr, std::size_t rhsStrLen);

    static _CharType& At(_CharType* srcStr, std::size_t srcStrLen, std::size_t index);

    static std::size_t Length(const _CharType* srcStr);

    static void Swap(_CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrBufferSize, _CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferSize);
};

template <typename _CharType>
inline StringTraits<_CharType>::StringTraits(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrBufferSize)
{
    StringTraits::Assign(srcStr, srcStrLen, destStr, destStrBufferSize);
}

template <typename _CharType>
inline StringTraits<_CharType>::StringTraits(_CharType* destStr, std::size_t destStrBufferSize, _CharType ch, std::size_t chCount)
{
    StringTraits::Assign(destStr, destStrBufferSize, ch, chCount);
}

template<typename _CharType>
inline void StringTraits<_CharType>::Assign(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrBufferSize)
{
    assert(destStrBufferSize > srcStrLen && "String buffer overflowed!");

    memcpy(destStr, srcStr, sizeof(_CharType) * (srcStrLen + 1));

    destStr[srcStrLen] = _CharType();
}

template <typename _CharType>
inline void StringTraits<_CharType>::Assign(_CharType* destStr, std::size_t destStrBufferSize, _CharType ch, std::size_t chCount)
{
    assert(destStrBufferSize > chCount && "String buffer overflowed!");

    std::size_t i = 0;
    while (i < chCount)
    {
        destStr[i++] = ch;
    }

    destStr[i] = _CharType();
}

template <typename _CharType>
inline void StringTraits<_CharType>::Append(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferSize)
{
    assert(destStrBufferSize > srcStrLen + destStrLen && "String buffer overflowed!");

    memcpy(&destStr[destStrLen], srcStr, sizeof(_CharType) * (srcStrLen + 1));

    destStr[srcStrLen + destStrLen] = _CharType();
}

template<typename _CharType>
inline void StringTraits<_CharType>::Append(_CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferSize, _CharType ch, std::size_t chCount)
{
    assert(destStrBufferSize > chCount + destStrLen && "String buffer overflowed!");

    chCount += destStrLen;
    while (destStrLen < chCount)
    {
        destStr[destStrLen++] = ch;
    }

    destStr[destStrLen] = _CharType();
}

template <typename _CharType>
inline std::size_t StringTraits<_CharType>::Find(const _CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrOffset, const _CharType* srcFindSubStr, std::size_t srcFindSubStrLen)
{
    const _CharType* foundStr = std::search(srcStr + srcStrOffset, srcStr + srcStrLen, srcFindSubStr, srcFindSubStr + srcFindSubStrLen);
    if (foundStr != srcStr + srcStrLen)
    {
        return static_cast<std::size_t>(foundStr - srcStr);
    }

    return NPos;
}

template<typename _CharType>
inline std::size_t StringTraits<_CharType>::RFind(const _CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrOffset, const _CharType* srcFindSubStr, std::size_t srcFindSubStrLen)
{
    const _CharType* foundStr = std::find_end(srcStr + srcStrOffset, srcStr + srcStrLen, srcFindSubStr, srcFindSubStr + srcFindSubStrLen);
    if (foundStr != srcStr + srcStrLen)
    {
        return static_cast<std::size_t>(foundStr - srcStr);
    }

    return NPos;
}

template <typename _CharType>
inline int32_t StringTraits<_CharType>::Compare(const _CharType* lhsStr, std::size_t lhsStrLen, const _CharType* rhsStr, std::size_t rhsStrLen)
{
    auto ans = CharTraitsType::compare(lhsStr, rhsStr, std::min(lhsStrLen, rhsStrLen));
    if (ans != 0)
    {
        return ans;
    }

    if (lhsStrLen < rhsStrLen)
    {
        return -1;
    }
    if (lhsStrLen > rhsStrLen)
    {
        return 1;
    }
    
    return 0;
}

template<typename _CharType>
inline _CharType& StringTraits<_CharType>::At(_CharType* srcStr, std::size_t srcStrLen, std::size_t index)
{
    assert(index <= srcStrLen && "String index out of range!");

    return srcStr[index];
}

template<typename _CharType>
inline std::size_t StringTraits<_CharType>::Length(const _CharType* srcStr)
{
    return CharTraitsType::length(srcStr);
}

template<typename _CharType>
inline void StringTraits<_CharType>::Swap(_CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrBufferSize, _CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferSize)
{
    std::swap_ranges(srcStr, srcStr + srcStrLen, destStr);
}

} /* namespace string */
} /* namespace tgon */
