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
    /* @brief   Verifies the file format is exact. */
    static bool VerifyFormat(const uint8_t* fileData, size_t fileDataBytes);

    /* @brief   Decodes the file to the image. */
    bool Import(const uint8_t* fileData, size_t fileDataBytes);
};

inline bool JpgImageProcessor::Import(const uint8_t* fileData, std::size_t fileDataBytes)
{
    if (VerifyFormat(fileData, fileDataBytes) == false)
    {
        return false;
    }

    return false;
}

inline bool JpgImageProcessor::VerifyFormat(const uint8_t* fileData, std::size_t fileDataBytes)
{
    if (fileDataBytes < 2)
    {
        return false;
    }

    return (fileData[0] == 0xFF && fileData[1] == 0xD8);
}

} /* namespace tgon */
