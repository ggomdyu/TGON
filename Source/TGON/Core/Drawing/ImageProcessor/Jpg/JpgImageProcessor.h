/**
 * @filename    JpgImageProcessor.h
 * @author      ggomdyu
 * @since       04/22/2018
 */

#pragma once
#include "../Generic/GenericImageProcessor.h"

namespace tgon
{

template <typename _AllocatorType>
class BasicJpgImageProcessor :
    public GenericImageProcessor<BasicJpgImageProcessor<_AllocatorType>, _AllocatorType>
{
/* @section Public constructor */
public:
    using GenericImageProcessor<BasicJpgImageProcessor<_AllocatorType>, _AllocatorType>::GenericImageProcessor;

/* @section Public method */
public:
    /* @brief   Verifies the importing file is exactly PNG. */
    static bool VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes);
    bool Import(const uint8_t* srcData, std::size_t srcDataBytes);
};

template <typename _AllocatorType>
inline bool BasicJpgImageProcessor<_AllocatorType>::Import(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (VerifyFormat(srcData, srcDataBytes) == false)
    {
        return false;
    }

    return false;
}

template <typename _AllocatorType>
inline bool BasicJpgImageProcessor<_AllocatorType>::VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (srcDataBytes < 2)
    {
        return false;
    }

    return (srcData[0] == 0xFF && srcData[1] == 0xD8);
}

using JpgImageProcessor = BasicJpgImageProcessor<std::allocator<uint8_t>>;

} /* namespace tgon */
