/**
 * @filename    WebPImageProcessor.h
 * @author      ggomdyu
 * @since       04/22/2018
 */

#pragma once
#include "../Generic/GenericImageProcessor.h"

namespace tgon
{

template <typename _AllocatorType = std::allocator<uint8_t>>
class WebPImageProcessor :
    public GenericImageProcessor<WebPImageProcessor<_AllocatorType>, _AllocatorType>
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
inline bool WebPImageProcessor<_AllocatorType>::Import(const uint8_t* srcData, uint32_t srcDataBytes)
{
    return false;
}

template <typename _AllocatorType>
inline bool WebPImageProcessor<_AllocatorType>::VerifyFormat(const uint8_t* srcData, uint32_t srcDataBytes)
{
    if (srcDataBytes < 12)
    {
        return false;
    }

    const char* header = reinterpret_cast<const char*>(&srcData[8]);
    return (header[0] == 'W' && header[1] == 'E' && header[2] == 'B' && header[3] == 'P');
}

} /* namespace tgon */  