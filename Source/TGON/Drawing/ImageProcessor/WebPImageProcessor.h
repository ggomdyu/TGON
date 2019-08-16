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
    /* @brief   Verifies the file format is exact. */
    static bool VerifyFormat(const uint8_t* fileData, size_t fileDataBytes);

    /* @brief   Decodes the file to the image. */
    bool Import(const uint8_t* fileData, size_t fileDataBytes);
};

inline bool WebPImageProcessor::Import(const uint8_t* fileData, std::size_t fileDataBytes)
{
    return false;
}

inline bool WebPImageProcessor::VerifyFormat(const uint8_t* fileData, std::size_t fileDataBytes)
{
    if (fileDataBytes < 12)
    {
        return false;
    }

    const char* header = reinterpret_cast<const char*>(&fileData[8]);
    return (header[0] == 'W' && header[1] == 'E' && header[2] == 'B' && header[3] == 'P');
}

} /* namespace tgon */  
