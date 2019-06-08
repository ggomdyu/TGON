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

TGON_API std::unique_ptr<uint8_t[]> LoadImageData(const char* filePath, int32_t* width, int32_t* height, int32_t* channels);

TGON_API std::unique_ptr<uint8_t[]> LoadImageData(const uint8_t* srcData, int32_t srcDataBytes, int32_t* width, int32_t* height, int32_t* channels);

TGON_API ImageFormat ConvertStringToImageFormat(const std::string_view& str);

template <std::size_t _ImageFormatStrLen>
inline ImageFormat ConvertStringToImageFormat(const char(&imageFormatStr)[_ImageFormatStrLen])
{
    return ConvertStringToImageFormat({imageFormatStr, _ImageFormatStrLen - 1});
}

} /* namespace tgon */
