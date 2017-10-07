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
    using CharTraits = std::char_traits<_CharType>;

/* @section Protected constructor */
protected:
    /**
     * @brief                   Copy string from source to destination.
     * @param [in] srcStrLen    The string to copy.
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
     *          The function series of Find will return this variable when searching sub-string does not exist.
     */
    static constexpr std::size_t NPos = static_cast<std::size_t>(-1);

/* @section Protected method */
protected:
    static std::size_t Find(const _CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrOffset, const _CharType* srcFindSubStr, std::size_t srcFindSubStrLen);

    static std::size_t RFind(const _CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrOffset, const _CharType* srcFindSubStr, std::size_t srcFindSubStrLen);

    static int32_t Compare(const _CharType* lhsStr, std::size_t lhsStrLen, const _CharType* rhsStr, std::size_t rhsStrLen);

    static void Append(_CharType* lhsStr, std::size_t lhsStrLen, const _CharType* rhsStr, std::size_t rhsStrLen);

    static void Assign(_CharType* destBuffer, std::size_t destBufferSize, _CharType ch, std::size_t chCount);
};

template <typename _CharType>
inline StringTraits<_CharType>::StringTraits(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrBufferSize)
{
    assert(destStrBufferSize > srcStrLen && "BasicFixedString buffer overflowed");

    memcpy(destStr, srcStr, srcStrLen + 1);
}

template <typename _CharType>
inline StringTraits<_CharType>::StringTraits(_CharType* destStr, std::size_t destStrBufferSize, _CharType ch, std::size_t chCount)
{
    assert(destStrBufferSize > chCount && "BasicFixedString buffer overflowed");

    std::size_t i = 0;
    while (i < chCount)
    {
        destStr[i++] = ch;
    }
    
    destStr[++i] = static_cast<_CharType>(0);
}

template <typename _CharType>
inline std::size_t StringTraits<_CharType>::Find(const _CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrOffset, const _CharType* srcFindSubStr, std::size_t srcFindSubStrLen)
{
    if ((srcStrOffset > srcStrLen) || ((srcStrLen - srcStrOffset) < srcFindSubStrLen))
    {
        return NPos;
    }

    if (srcFindSubStrLen == 0)
    {
        return srcStrOffset;
    }

    const _CharType* foundStr = std::search(srcStr + srcStrOffset, srcStr + srcStrLen, srcFindSubStr, srcFindSubStr + srcFindSubStrLen);
    if (foundStr == srcStr + srcStrLen)
    {
        return NPos;
    }

    return static_cast<std::size_t>(foundStr - srcStr);
}

template <typename _CharType>
inline int32_t StringTraits<_CharType>::Compare(const _CharType* lhsStr, std::size_t lhsStrLen, const _CharType* rhsStr, std::size_t rhsStrLen)
{
    auto minSize = lhsStrLen < rhsStrLen ? lhsStrLen : rhsStrLen;

    auto ans = std::char_traits<_CharType>::compare(lhsStr, rhsStr, minSize);
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

template <typename _CharType>
inline void StringTraits<_CharType>::Append(const _CharType* lhsStr, std::size_t lhsStrLen, const _CharType* rhsStr, std::size_t rhsStrLen)
{
    
}

template <typename _CharType>
inline void StringTraits<_CharType>::Assign(_CharType* destBuffer, std::size_t destBufferSize, _CharType ch, std::size_t chCount)
{
    assert(destBufferSize > chCount && "BasicFixedString buffer overflowed");

    std::size_t i = 0;
    while (i < chCount)
    {
		destBuffer[i++] = ch;
    }

	destBuffer[i] = static_cast<_CharType>(0);
}

} /* namespace string */
} /* namespace tgon */
