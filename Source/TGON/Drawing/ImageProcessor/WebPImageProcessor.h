/**
 * @file    WebPImageProcessor.h
 * @author  ggomdyu
 * @since   04/22/2018
 */

#pragma once
#include "BaseImageProcessor.h"

namespace tgon
{

class WebPImageProcessor :
    public BaseImageProcessor<WebPImageProcessor>
{
/* @section Constructor */
public:
    using BaseImageProcessor<WebPImageProcessor>::BaseImageProcessor;

/* @section Method */
public:
    /* @brief   Verifies the importing file is exactly PNG. */
    static bool VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes);
    bool Import(const uint8_t* srcData, std::size_t srcDataBytes);
};

inline bool WebPImageProcessor::Import(const uint8_t* srcData, std::size_t srcDataBytes)
{
    return false;
}

inline bool WebPImageProcessor::VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (srcDataBytes < 12)
    {
        return false;
    }

    const char* header = reinterpret_cast<const char*>(&srcData[8]);
    return (header[0] == 'W' && header[1] == 'E' && header[2] == 'B' && header[3] == 'P');
}

} /* namespace tgon */  
