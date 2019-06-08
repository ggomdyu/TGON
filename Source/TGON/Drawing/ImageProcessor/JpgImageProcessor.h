/**
 * @file    JpgImageProcessor.h
 * @author  ggomdyu
 * @since   04/22/2018
 */

#pragma once
#include "BaseImageProcessor.h"

namespace tgon
{

class JpgImageProcessor :
    public BaseImageProcessor<JpgImageProcessor>
{
/* @section Constructor */
public:
    using BaseImageProcessor<JpgImageProcessor>::BaseImageProcessor;

/* @section Method */
public:
    /* @brief   Verifies the importing file is exactly PNG. */
    static bool VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes);
    bool Import(const uint8_t* srcData, std::size_t srcDataBytes);
};

inline bool JpgImageProcessor::Import(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (VerifyFormat(srcData, srcDataBytes) == false)
    {
        return false;
    }

    return false;
}

inline bool JpgImageProcessor::VerifyFormat(const uint8_t* srcData, std::size_t srcDataBytes)
{
    if (srcDataBytes < 2)
    {
        return false;
    }

    return (srcData[0] == 0xFF && srcData[1] == 0xD8);
}

} /* namespace tgon */
