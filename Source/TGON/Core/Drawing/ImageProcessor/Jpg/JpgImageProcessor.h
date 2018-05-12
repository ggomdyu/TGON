/**
 * @filename    JpgImageProcessor.h
 * @author      ggomdyu
 * @since       04/22/2018
 */

#pragma once
#include "../Generic/GenericImageProcessor.h"

namespace tgon
{

template <typename _AllocatorType = std::allocator<uint8_t>>
class JpgImageProcessor :
    public GenericImageProcessor<JpgImageProcessor<_AllocatorType>, _AllocatorType>
{
/* @section Public constructor */
public:
    using GenericImageProcessor::GenericImageProcessor;

/* @section Public method */
public:
    /* @brief   Verifies the importing file is exactly PNG. */
    static bool VerifyFormat(const uint8_t* srcData, uint32_t srcDataBytes);
    bool Import(const uint8_t* srcData, uint32_t srcDataBytes);
};

template <typename _AllocatorType>
inline bool JpgImageProcessor<_AllocatorType>::Import(const uint8_t* srcData, uint32_t srcDataBytes)
{
    if (VerifyFormat(srcData, srcDataBytes) == false)
    {
        return false;
    }

    return false;
}

template <typename _AllocatorType>
inline bool JpgImageProcessor<_AllocatorType>::VerifyFormat(const uint8_t* srcData, uint32_t srcDataBytes)
{
    if (srcDataBytes < 2)
    {
        return false;
    }

    return (srcData[0] == 0xFF && srcData[1] == 0xD8);
}

} /* namespace tgon */