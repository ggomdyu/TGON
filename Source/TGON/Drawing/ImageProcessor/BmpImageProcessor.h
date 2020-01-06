/**
 * @file    BmpImageProcessor.h
 * @author  ggomdyu
 * @since   04/22/2018
 * @warning This image processor supports only Windows bmp format, not for os2!
 */

#pragma once
#include "ImageProcessor.h"

namespace tgon
{

class BmpImageProcessor :
    public ImageProcessor
{
/* @section Method */
public:
    static bool IsExactFormat(const gsl::span<const std::byte>& fileData);
    bool Initialize(const gsl::span<const std::byte>& fileData) override;
};

inline bool BmpImageProcessor::Initialize(const gsl::span<const std::byte>& fileData)
{
    if (BmpImageProcessor::IsExactFormat(fileData) == false)
    {
        return false;
    }

    return false;
}

inline bool BmpImageProcessor::IsExactFormat(const gsl::span<const std::byte>& fileData)
{
    if (fileData.size() < 2)
    {
        return false;
    }

    return (fileData[0] == std::byte('B') && fileData[1] == std::byte('M'));
}
    
} /* namespace tgon */  