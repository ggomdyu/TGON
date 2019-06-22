/**
 * @file    ImageUtility.h
 * @author  ggomdyu
 * @since   06/06/2019
 */

#pragma once
#include <cstdint>
#include <string_view>

#include "Platform/Config.h"

#include "ImageType.h"

namespace tgon
{

TGON_API std::unique_ptr<uint8_t[]> LoadImageData(const char* filePath, int32_t* destWidth, int32_t* destHeight);

TGON_API std::unique_ptr<uint8_t[]> LoadImageData(const uint8_t* fileData, int32_t fileDataBytes, int32_t* destWidth, int32_t* destHeight);

TGON_API ImageFormat ConvertStringToImageFormat(const std::string_view& str);

constexpr int32_t GetBytesPerPixel(PixelFormat pixelFormat)
{
    constexpr int32_t bitsPerPixelTable[] = {
        0, // Unknown
        4, // RGBA8888
        3, // RGB888
        2, // RGBA4444
        1, // R8
    };

    return bitsPerPixelTable[static_cast<int>(pixelFormat)];
}

constexpr int32_t GetBitsPerPixel(PixelFormat pixelFormat)
{
    return GetBytesPerPixel(pixelFormat) * 8;
}

} /* namespace tgon */
