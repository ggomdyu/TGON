#include "PrecompiledHeader.h"

#define TGON_PREFER_LOWLEVEL_IMAGE_IMPORTER 1

#if TGON_PREFER_LOWLEVEL_IMAGE_IMPORTER == 0
#   define STB_IMAGE_IMPLEMENTATION
#   define STB_IMAGE_WRITE_IMPLEMENTATION
#   ifdef _MSC_VER
#      define STBI_MSC_SECURE_CRT
#   endif
#   include <stb_image.h>
#endif

#include "String/StringTraits.h"
#include "String/Hash.h"

#if TGON_PREFER_LOWLEVEL_IMAGE_IMPORTER
#   include "ImageProcessor/BmpImageProcessor.h"
#   include "ImageProcessor/JpgImageProcessor.h"
#   include "ImageProcessor/PngImageProcessor.h"
#endif
#include "ImageProcessor/WebPImageProcessor.h"

#include "ImageUtility.h"

namespace tgon
{

uint8_t* LoadImageData(const char* filePath, int32_t* width, int32_t* height, int32_t* channels)
{
#if defined(_MSC_VER) && _MSC_VER >= 1400
    FILE* file = nullptr;
    fopen_s(&file, filePath, "rb");
#else
    FILE* file = fopen(filePath, "rb");
#endif
    if (file == nullptr)
    {
        return nullptr;
    }
    
    fseek(file, 0, SEEK_END);
    int32_t fileSize = static_cast<int32_t>(ftell(file));
    fseek(file, 0, SEEK_SET);

    auto fileData = std::make_unique<uint8_t[]>(fileSize);
    fread(fileData.get(), 1, fileSize, file);
    fclose(file);

    return LoadImageData(fileData.get(), fileSize, width, height, channels);
}

uint8_t* LoadImageData(const uint8_t* srcData, int32_t srcDataBytes, int32_t* width, int32_t* height, int32_t* channels)
{
    uint8_t* ret;
    auto d = [&](const auto& imageProcessor)
    {
        if (imageProcessor.VerifyFormat(srcData, srcDataBytes))
        {
            *ret = std::move(imageProcessor.GetImageData());
            *width = imageProcessor.GetWidth();
            *height = imageProcessor.GetHeight();
            *channels = imageProcessor.GetChannels();
        }
    };

    d(PngImageProcessor{});

#if TGON_PREFER_LOWLEVEL_IMAGE_IMPORTER
    /*if (PngImage)
    {
    case ImageFormat::Png:
    {
        PngImageProcessor imageProcessor(srcData, srcDataBytes);
        if (imageProcessor.IsValid())
        {
            m_imageData = std::move(imageProcessor.GetImageData());
            m_width = imageProcessor.GetWidth();
            m_height = imageProcessor.GetHeight();
            m_channels = imageProcessor.GetChannels();
            m_colorDepth = imageProcessor.GetColorDepth();
            m_pixelFormat = imageProcessor.GetPixelFormat();
            return true;
        }
    }
    return false;

    case ImageFormat::Jpg:
    {
        JpgImageProcessor imageProcessor(srcData, srcDataBytes);
        if (imageProcessor.IsValid())
        {
            m_imageData = std::move(imageProcessor.GetImageData());
            m_width = imageProcessor.GetWidth();
            m_height = imageProcessor.GetHeight();
            m_channels = imageProcessor.GetChannels();
            m_colorDepth = imageProcessor.GetColorDepth();
            m_pixelFormat = imageProcessor.GetPixelFormat();
            return true;
        }
    }
    return false;

    case ImageFormat::WebP:
    {
        WebPImageProcessor imageProcessor(srcData, srcDataBytes);
        if (imageProcessor.IsValid())
        {
            m_imageData = std::move(imageProcessor.GetImageData());
            m_width = imageProcessor.GetWidth();
            m_height = imageProcessor.GetHeight();
            m_channels = imageProcessor.GetChannels();
            m_colorDepth = imageProcessor.GetColorDepth();
            m_pixelFormat = imageProcessor.GetPixelFormat();
            return true;
        }
    }
    return false;

    case ImageFormat::Bmp:
    {
        BmpImageProcessor imageProcessor(srcData, srcDataBytes);
        if (imageProcessor.IsValid())
        {
            m_imageData = std::move(imageProcessor.GetImageData());
            m_width = imageProcessor.GetWidth();
            m_height = imageProcessor.GetHeight();
            m_channels = imageProcessor.GetChannels();
            m_colorDepth = imageProcessor.GetColorDepth();
            m_pixelFormat = imageProcessor.GetPixelFormat();
            return true;
        }
    }
    return false;

    default:
        return false;
    }*/
#else   
    return stbi_load_from_memory(reinterpret_cast<const stbi_uc*>(srcData), srcDataBytes, width, height, channels, 4);
#endif
}

ImageFormat ConvertStringToImageFormat(const std::string_view& str)
{
    char lowercaseStr[32]{};
    BasicStringTraits<char>::ToLower(str, lowercaseStr, std::extent<decltype(lowercaseStr)>::value);

    switch (X65599Hash(lowercaseStr))
    {
    case TGON_X65599("bmp"):
        return ImageFormat::Bmp;
    case TGON_X65599("jpg"):
        return ImageFormat::Jpg;
    case TGON_X65599("jpeg"):
        return ImageFormat::Jpeg;
    case TGON_X65599("png"):
        return ImageFormat::Png;
    case TGON_X65599("tiff"):
        return ImageFormat::Tiff;
    case TGON_X65599("gif"):
        return ImageFormat::Gif;
    case TGON_X65599("webp"):
        return ImageFormat::WebP;
    default:
        return ImageFormat::Unknown;
    }
}

} /* namespace tgon */