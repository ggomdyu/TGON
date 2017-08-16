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

/* @section Ctor/Dtor */
protected:
    constexpr StringTraits() noexcept = default;
    constexpr StringTraits(const _CharType* copySrcStr, _CharType* copyDestStr, std::size_t copySrcStrLength);
    constexpr StringTraits(_CharType* destStr, _CharType ch, std::size_t chAssignCount);

/* @section Public variable */
public:
    static constexpr std::size_t NPos = static_cast<std::size_t>(-1);

/* @section Protected method */
protected:
    static std::size_t Find(const _CharType* srcStr, std::size_t srcStrLength, const _CharType* srcFindStr, std::size_t offset, std::size_t srcFindStrLength);

    static int32_t Compare(const _CharType* lhsStr, std::size_t lhsStrLength, const _CharType* rhsStr, std::size_t rhsStrLength);

    static void Assign(_CharType* destBuffer, std::size_t destBufferSize, _CharType ch, std::size_t chCount);
};

template <typename _CharType>
constexpr StringTraits<_CharType>::StringTraits(const _CharType* copySrcStr, _CharType* copyDestStr, std::size_t copySrcStrLength)
{
    //assert(destStrBufferSize > chAssignCount && "BasicFixedString buffer overflowed");

    std::size_t i = 0;
    while (i < copySrcStrLength)
    {
        copyDestStr[i] = copySrcStr[i];
        ++i;
    }

    copyDestStr[++i] = static_cast<_CharType>(0);
}

template <typename _CharType>
constexpr StringTraits<_CharType>::StringTraits(_CharType* destStr, _CharType ch, std::size_t chAssignCount)
{
    //assert(destStrBufferSize > chAssignCount && "BasicFixedString buffer overflowed");

    std::size_t i = 0;
    while (i < chAssignCount)
    {
        destStr[i++] = ch;
    }
    
    destStr[++i] = static_cast<_CharType>(0);
}

template <typename _CharType>
inline std::size_t StringTraits<_CharType>::Find(const _CharType* srcStr, std::size_t srcStrLength, const _CharType* srcFindSubStr, std::size_t srcStrOffset, std::size_t srcFindSubStrLength)
{
    if ((srcStrOffset > srcStrLength) || ((srcStrLength - srcStrOffset) < srcFindSubStrLength))
    {
        return NPos;
    }

    if (srcFindSubStrLength == 0)
    {
        return srcStrOffset;
    }

    const _CharType* foundStr = std::search(srcStr + srcStrOffset, srcStr + srcStrLength, srcFindSubStr, srcFindSubStr + srcFindSubStrLength);
    if (foundStr == srcStr + srcStrLength)
    {
        return NPos;
    }

    return static_cast<std::size_t>(foundStr - srcStr);
}

template <typename _CharType>
inline int32_t StringTraits<_CharType>::Compare(const _CharType* lhsStr, std::size_t lhsStrLength, const _CharType* rhsStr, std::size_t rhsStrLength)
{
    auto minSize = lhsStrLength < rhsStrLength ? lhsStrLength : rhsStrLength;

    auto ans = std::char_traits<_CharType>::compare(lhsStr, rhsStr, minSize);
    if (ans != 0)
    {
        return ans;
    }

    if (lhsStrLength < rhsStrLength)
    {
        return -1;
    }
    if (lhsStrLength > rhsStrLength)
    {
        return 1;
    }
    
    return 0;
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
