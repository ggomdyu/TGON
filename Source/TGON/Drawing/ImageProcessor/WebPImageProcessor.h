/**
 * @file    WebPImageProcessor.h
 * @author  ggomdyu
 * @since   04/22/2018
 */

#pragma once
#include "ImageProcessor.h"

namespace tgon
{


class WebPImageProcessor :
    public ImageProcessor
{
/* @section Method */
public:
    static bool IsExactFormat(const gsl::span<const std::byte>& fileData);
    bool Initialize(const gsl::span<const std::byte>& fileData) override;
};

inline bool WebPImageProcessor::Initialize(const gsl::span<const std::byte>& fileData)
{
    if (WebPImageProcessor::IsExactFormat(fileData) == false)
    {
        return false;
    }

    return false;
}

inline bool WebPImageProcessor::IsExactFormat(const gsl::span<const std::byte>& fileData)
{
    if (fileData.size() < 12)
    {
        return false;
    }

    return memcmp(&fileData[0], "WEBP", 4) == 0;
}
    
} /* namespace tgon */  
