/**
 * @file    ImageUtility.h
 * @author  ggomdyu
 * @since   04/10/2018
 */

#pragma once
#include <cstdint>

#include "Core/Platform/Config.h"

#include "ImageType.h"

namespace tgon
{

class TGON_API ImageUtilty
{
/**@section Method */
public:
    ImageFormat ConvertStringToImageFormat(const char* imageFormatStr, std::size_t imageFormatStrLen);

    template <std::size_t _ImageFormatStrLen>
    ImageFormat ConvertStringToImageFormat(const char(&imageFormatStr)[_ImageFormatStrLen]);
};

template <std::size_t _ImageFormatStrLen>
inline ImageFormat ImageUtilty::ConvertStringToImageFormat(const char(&imageFormatStr)[_ImageFormatStrLen])
{
    return ConvertStringToImageFormat(imageFormatStr, _ImageFormatStrLen - 1);
}

} /* namespace tgon */  
