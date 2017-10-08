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
    /**
     * @brief                   Copy string from source to destination.
     * @param [in] srcStrLen    The string to copy.
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

    static _CharType& At(const _CharType* srcStr, std::size_t index);
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
    assert(destStrBufferSize > srcStrLen && "String buffer overflowed");

    memcpy(destStr, srcStr, srcStrLen + 1);
}

template <typename _CharType>
inline void StringTraits<_CharType>::Assign(_CharType* destStr, std::size_t destStrBufferSize, _CharType ch, std::size_t chCount)
{
    assert(destStrBufferSize > chCount && "String buffer overflowed");

    std::size_t i = 0;
    while (i < chCount)
    {
        destStr[i++] = ch;
    }

    destStr[i] = static_cast<_CharType>(0);
}

template <typename _CharType>
inline void StringTraits<_CharType>::Append(const _CharType* srcStr, std::size_t srcStrLen, _CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferSize)
{
    assert(destStrBufferSize > srcStrLen + destStrLen && "String buffer overflowed");

    memcpy(&destStr[destStrLen], srcStr, srcStrLen + 1);
}

template<typename _CharType>
inline void StringTraits<_CharType>::Append(_CharType* destStr, std::size_t destStrLen, std::size_t destStrBufferSize, _CharType ch, std::size_t chCount)
{
    assert(destStrBufferSize > chCount + destStrLen && "String buffer overflowed");

    chCount += destStrLen;
    while (destStrLen < chCount)
    {
        destStr[destStrLen++] = ch;
    }

    destStr[destStrLen] = static_cast<_CharType>(0);
}

template <typename _CharType>
inline std::size_t StringTraits<_CharType>::Find(const _CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrOffset, const _CharType* srcFindSubStr, std::size_t srcFindSubStrLen)
{
    const _CharType* foundStr = std::search(srcStr + srcStrOffset, srcStr + srcStrLen, srcFindSubStr, srcFindSubStr + srcFindSubStrLen);
    if (foundStr == srcStr + srcStrLen)
    {
        return NPos;
    }

    return static_cast<std::size_t>(foundStr - srcStr);
}

template<typename _CharType>
inline std::size_t StringTraits<_CharType>::RFind(const _CharType* srcStr, std::size_t srcStrLen, std::size_t srcStrOffset, const _CharType* srcFindSubStr, std::size_t srcFindSubStrLen)
{
    using std::min;

    const _CharType* foundStr = &srcStr[min(srcStrOffset, srcStrLen - srcFindSubStrLen)];
    while (true)
    {
        auto ans = std::char_traits<_CharType>::compare(foundStr, srcFindSubStr, srcFindSubStrLen);
        if (ans == 0)
        {
            return static_cast<std::size_t>(foundStr - srcStr);
        }
        else
        {
            if (foundStr == srcStr)
            {
                break;
            }

            --foundStr;
        }
    }

    return NPos;
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

template<typename _CharType>
inline _CharType& StringTraits<_CharType>::At(const _CharType* srcStr, std::size_t index)
{
    return srcStr[index];
}

} /* namespace string */
} /* namespace tgon */